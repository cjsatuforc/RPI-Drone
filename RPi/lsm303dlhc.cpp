#include "lsm303dlhc.h"
#include "systimer.h"

LSM303DLHCAccelerometer::LSM303DLHCAccelerometer() :
	I2CSensorInterface(0x19)
{

}

void LSM303DLHCAccelerometer::SetFullScale(LSM303DLHCAccelerometer::FullScale FS)
{
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
}

void LSM303DLHCAccelerometer::SetOutputDataRate(LSM303DLHCAccelerometer::OutputDataRate ODR)
{
	uint8_t data = 0;
	uint8_t e = ReadRegister8(0x20, &data);
	if (e != 0)
		return;

	data &= ~0b11110000;
	data |= ODR << 4;
	e = WriteRegister8(0x20, data);
	if (e != 0)
		return;

	mODR = ODR;
}

void LSM303DLHCAccelerometer::SetHighResolution(bool val)
{
	if (mHighResolution == val)
		return;
	uint8_t data = 0;
	uint8_t e = ReadRegister8(0x23, &data);
	if (e != 0)
		return;

	data &= ~0b00001000;
	data |= (val & 0b1) << 3;
	e = WriteRegister8(0x23, data);
	if (e != 0)
		return;
	mHighResolution = val;
}

void LSM303DLHCAccelerometer::Tick()
{
	uint8_t stat = 0;
	uint8_t e = ReadRegister8(0x27, &stat);
	if (e != 0)
		printf("Error: %u", e);

	mHasNewData = stat & (1 << 3);
	mHasOverrun = stat & (1 << 7);
	if (mHasNewData)
	{
		uint8_t data[6];
		e = RequestFrom(0x28, 6, data);
		if (e != 0)
			printf("Error: %u", e);

		mRawX = data[0] | (data[1] << 8);
		mRawY = data[2] | (data[3] << 8);
		mRawZ = data[4] | (data[5] << 8);
		float sCorr = GetSensitivityCorrection();

		mX = mRawX * sCorr;
		mY = mRawY * sCorr;
		mZ = mRawZ * sCorr;
	}

}

bool LSM303DLHCAccelerometer::HasNewData() const
{
	return mHasNewData;
}

bool LSM303DLHCAccelerometer::HasOverrun() const
{
	return mHasOverrun;
}

bool LSM303DLHCAccelerometer::IsSaturated() const
{
	return	mRawX == INT16_MAX || mRawX == INT16_MIN ||
			mRawY == INT16_MAX || mRawY == INT16_MIN ||
			mRawZ == INT16_MAX || mRawZ == INT16_MIN;
}

int16_t LSM303DLHCAccelerometer::GetRawX() const
{
	return mRawX;
}

int16_t LSM303DLHCAccelerometer::GetRawY() const
{
	return mRawY;
}

int16_t LSM303DLHCAccelerometer::GetRawZ() const
{
	return mRawZ;
}

float LSM303DLHCAccelerometer::GetX() const
{
	return mX;
}

float LSM303DLHCAccelerometer::GetY() const
{
	return mY;
}

float LSM303DLHCAccelerometer::GetZ() const
{
	return mZ;
}

float LSM303DLHCAccelerometer::GetSensitivityCorrection() const
{
	return (mFS == FS2G) ? 0.00006103515625 : (mFS == FS4G) ? 0.0001220703125 : (mFS == FS8G) ? 0.000244140625 : 0.00048828125;
}

LSM303DLHCMagnetometer::LSM303DLHCMagnetometer() :
	I2CSensorInterface(0x1E)
{
	WriteRegister8(0x02, 0x00);
}

void LSM303DLHCMagnetometer::SetFullScale(FullScale FS)
{
	uint8_t data = 0;
	uint8_t e = ReadRegister8(0x01, &data);
	if (e != 0)
		return;

	data &= ~0b11100000;
	data |= FS << 5;
	e = WriteRegister8(0x01, data);
	if (e != 0)
		return;

	mFullScale = FS;
}

void LSM303DLHCMagnetometer::SetOutputDataRate(OutputDataRate ODR)
{
	uint8_t data = 0;
	uint8_t e = ReadRegister8(0x00, &data);
	if (e != 0)
		return;

	data &= ~0b00011100;
	data |= ODR << 2;
	e = WriteRegister8(0x00, data);
	if (e != 0)
		return;

	mOutputDataRate = ODR;
}

void LSM303DLHCMagnetometer::Tick()
{
	uint8_t stat = 0;
	uint8_t e = ReadRegister8(0x09, &stat);
	if (e != 0)
		printf("Error: %u", e);

	mHasNewData = stat & (0b1);

	if (mHasNewData)
	{
		uint8_t data[6];
		e = RequestFrom(0x03, 6, data);
		if (e != 0)
			printf("Error: %u", e);

		mRawX = data[0] | (data[1] << 8);
		mRawY = data[2] | (data[3] << 8);
		mRawZ = data[4] | (data[5] << 8);
		float sCorr = /*GetSensitivityCorrection()*/ 1.0f;

		mX = mRawX * sCorr;
		mY = mRawY * sCorr;
		mZ = mRawZ * sCorr;
	}
}

bool LSM303DLHCMagnetometer::HasNewData() const
{
	return mHasNewData;
}

bool LSM303DLHCMagnetometer::IsSaturated() const
{
	return	mRawX == INT16_MAX || mRawX == INT16_MIN ||
			mRawY == INT16_MAX || mRawY == INT16_MIN ||
			mRawZ == INT16_MAX || mRawZ == INT16_MIN;
}

int16_t LSM303DLHCMagnetometer::GetRawX() const
{
	return mRawX;
}

int16_t LSM303DLHCMagnetometer::GetRawY() const
{
	return mRawY;
}

int16_t LSM303DLHCMagnetometer::GetRawZ() const
{
	return mRawZ;
}

float LSM303DLHCMagnetometer::GetX() const
{
	return mX;
}

float LSM303DLHCMagnetometer::GetY() const
{
	return mY;
}

float LSM303DLHCMagnetometer::GetZ() const
{
	return mZ;
}
