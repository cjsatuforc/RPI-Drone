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
	bool IsSaturated() const;

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
	enum OutputDataRate
	{
		ODR0Hz75 = 0b000, //0.75Hz
		ODR1Hz5 = 0b001, //1.5Hz
		ODR3Hz = 0b010, //3Hz
		ODR7Hz5 = 0b011, //7.5Hz
		ODR15Hz = 0b100, //15Hz
		ODR30Hz = 0b101, //30Hz
		ODR75Hz = 0b110, //75Hz
		ODR220Hz = 0b111 //220Hz
	};
	void SetFullScale(FullScale FS);
	void SetOutputDataRate(OutputDataRate ODR);

	void Calibrate();
	void Tick();
	bool HasNewData() const;
	bool IsSaturated() const;

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

	float mX;
	float mY;
	float mZ;

	bool mHasNewData;

	FullScale mFullScale;
	OutputDataRate mOutputDataRate;
};
