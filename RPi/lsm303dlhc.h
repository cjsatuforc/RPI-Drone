#pragma once

#include "I2CSensorInterface.h"


class LSM303DLHCAccelerometer : public I2CSensorInterface
{
public:
	LSM303DLHCAccelerometer();
	LSM303DLHCAccelerometer(const LSM303DLHCAccelerometer& other) = delete;
	LSM303DLHCAccelerometer(LSM303DLHCAccelerometer&& other) = delete;

	enum FullScale
	{
		FS2G = 0b00, //+/-2G
		FS4G = 0b01, //+/-4G
		FS8G = 0b10, //+/-8G
		FS16G = 0b11 //+/-16G
	};
	enum OutputDataRate
	{
		PowerDown = 0b0000,
		Normal_LowPower_1Hz = 0b0001,
		Normal_LowPower_10Hz = 0b0010,
		Normal_LowPower_25Hz = 0b0011,
		Normal_LowPower_50Hz = 0b0100,
		Normal_LowPower_100Hz = 0b0101,
		Normal_LowPower_200Hz = 0b0110,
		Normal_LowPower_400Hz = 0b0111,
		LowPower_1620Hz = 0b1000,
		Normal_1344Hz_LowPower_5376Hz = 0b1001
	};
	void SetFullScale(FullScale FS);
	void SetOutputDataRate(OutputDataRate ODR);
	void SetHighResolution(bool val);

	void Tick();
	bool HasNewData() const;
	bool HasOverrun() const;

	int16_t GetRawX() const;
	int16_t GetRawY() const;
	int16_t GetRawZ() const;

	float GetX() const;
	float GetY() const;
	float GetZ() const;

private:
	int16_t mRawX;
	int16_t mRawY;
	int16_t mRawZ;

	int16_t mAvgX;
	int16_t mAvgY;
	int16_t mAvgZ;

	float mX;
	float mY;
	float mZ;

	bool mHasNewData;
	bool mHasOverrun;
	FullScale mFS = FS2G;
	OutputDataRate mODR = PowerDown;
	bool mHighResolution = false;
	float GetSensitivityCorrection() const;
};

class LSM303DLHCMagnetometer : public I2CSensorInterface
{
public:
	LSM303DLHCMagnetometer();
	LSM303DLHCMagnetometer(const LSM303DLHCMagnetometer& other) = delete;
	LSM303DLHCMagnetometer(LSM303DLHCMagnetometer&& other) = delete;

	enum FullScale
	{
		FS1Gs3, //1.3 gauss
		FS1Gs9, //1.9 gauss
		FS2Gs5, //2.5 gauss
		FS4Gs0, //4.0 gauss
		FS4Gs7, //4.7 gauss
		FS5Gs6, //5.6 gauss
		FS8Gs1 //8.1 gauss
	};
	void SetFullScale(FullScale FS);

	void Calibrate();
	void Tick();

private:
	FullScale mFullScale;
};
