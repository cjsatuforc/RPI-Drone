#include "l3g4200d.h"
#include "systimer.h"

L3G4200D::L3G4200D() :
	I2CSensorInterface(0x69),
	mTimeSinceLastRead(0.0L),
	mRawX(0),
	mRawY(0),
	mRawZ(0),
	mX(0.0L),
	mY(0.0L),
	mZ(0.0L),
	mHasNewData(false),
	mHasOverrun(false),
	mIsCalibrated(false),
	mHPFEnabled(false),
	mLPFEnabled(false)
{
	WriteRegister8(0x24, 0x80); //Reboot Sensor Memory
	RPI_WaitMicroSeconds(10);
}

void L3G4200D::SetOutputDataRate(L3G4200DOutputDataRate ODR)
{
	if (mODR != ODR)
	{
		uint8_t data = 0;
		uint8_t e = ReadRegister8(0x20, &data);
		if (e != 0)
			return;
		data &= ~0b11000000;
		data |= ODR << 6;
		e = WriteRegister8(0x20, data);
		if (e != 0)
			return;
		mODR = ODR;
	}
}

void L3G4200D::SetBandwidth(L3G4200DBandwidth BW)
{
	if (mBW != BW)
	{
		uint8_t data = 0;
		uint8_t e = ReadRegister8(0x20, &data);
		if (e != 0)
			return;
		data &= ~0b00110000;
		data |= BW << 4;
		e = WriteRegister8(0x20, data);
		if (e != 0)
			return;
		mBW = BW;
	}
}

void L3G4200D::SetFullScale(L3G4200DFullScale FS)
{
	if (FS == mFS)
		return;
	uint8_t data = 0;
	uint8_t e = ReadRegister8(0x23, &data);
	if (e != 0)
		return;
	data &= ~0b00110000;
	data |= FS << 4;
	e = WriteRegister8(0x23, data);
	if (e != 0)
		return;
	mFS = FS;
	mIsCalibrated = false;
}

void L3G4200D::SetPower(bool val)
{
	uint8_t data = 0;
	uint8_t e = ReadRegister8(0x20, &data);
	if (e != 0)
		return;
	data &= ~0b1000;
	data |= (val & 1) << 3;
	e = WriteRegister8(0x20, data);
	if (e != 0)
		return;

	mLastTickMs = RPI_GetSystemTimer()->counter();
}

void L3G4200D::SetLPFEnabled(bool val)
{
	if (mLPFEnabled != val)
	{
		mLPFEnabled = val;
		UpdateLPFHPFConfig();
	}
}

void L3G4200D::SetHPFEnabled(bool val)
{
	if (mHPFEnabled != val)
	{
		mHPFEnabled = val;
		UpdateLPFHPFConfig();
	}
}

void L3G4200D::Calibrate()
{
	long double x = 0.0L, y = 0.0L, z = 0.0L;

	size_t n = 1600;
	size_t i = 0;
	while (i < n)
	{
		Tick();
		if (HasNewData())
		{
			++i;
			x += GetRawX();
			y += GetRawY();
			z += GetRawZ();
		}
	}

	mAvgX = x / n;
	mAvgY = y / n;
	mAvgZ = z / n;

	mIsCalibrated = true;
}

void L3G4200D::Tick()
{
	uint8_t stat = 0;
	uint8_t e = ReadRegister8(0x27, &stat);
	if (e != 0)
		printf("Error: %u", e);

	mHasNewData = stat & (1 << 3);
	mHasOverrun = stat & (1 << 7);
	uint64_t curMs = RPI_GetSystemTimer()->counter();
	float deltaTime = (long double)(curMs - mLastTickMs) / 1000000.0L;
	mLastTickMs = curMs;
	if (mHasNewData)
	{
		uint8_t data[6];
		e = RequestFrom(0x28, 6, data);
		if (e != 0)
			printf("Error: %u", e);

		mRawX = data[0] | (data[1] << 8);
		mRawY = data[2] | (data[3] << 8);
		mRawZ = data[4] | (data[5] << 8);

		if (mIsCalibrated)
		{
			mRawX -= mAvgX;
			mRawY -= mAvgY;
			mRawZ -= mAvgZ;

			float sCorr = GetSensitivityCorrection();
			
			mX += mRawX * mTimeSinceLastRead * sCorr;
			mY += mRawY * mTimeSinceLastRead * sCorr;
			mZ += mRawZ * mTimeSinceLastRead * sCorr;
		}

		mTimeSinceLastRead = 0.0f;
	}	
	mTimeSinceLastRead += deltaTime;
}

bool L3G4200D::HasNewData() const
{
	return mHasNewData;
}

bool L3G4200D::HasOverrun() const
{
	return mHasOverrun;
}

bool L3G4200D::IsCalibrated() const
{
	return mIsCalibrated;
}

int16_t L3G4200D::GetRawX() const
{
	return mRawX;
}

int16_t L3G4200D::GetRawY() const
{
	return mRawY;
}

int16_t L3G4200D::GetRawZ() const
{
	return mRawZ;
}

float L3G4200D::GetX() const
{
	return mX;
}

float L3G4200D::GetY() const
{
	return mY;
}

float L3G4200D::GetZ() const
{
	return mZ;
}

void L3G4200D::UpdateLPFHPFConfig()
{
	uint8_t data = 0;
	uint8_t e = ReadRegister8(0x24, &data);
	if (e != 0)
		return;
	data &= ~0b00011111;
	data |= (mHPFEnabled & 0b1) << 4;

	data |= ((mHPFEnabled & 0b1) << 2) | (mHPFEnabled & 0b1);
	data |= ((mLPFEnabled & 0b1) << 3) | ((mLPFEnabled & 0b1) << 1);

	WriteRegister8(0x24, data);
}

float L3G4200D::GetSensitivityCorrection() const
{
	return (mFS == FS250) ? 0.00875f : (mFS == FS500) ? 0.0175f : 0.07f;
}
