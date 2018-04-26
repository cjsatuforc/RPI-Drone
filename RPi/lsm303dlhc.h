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
	void SetFullScale(FullScale FS);

	void Calibrate();
	void Tick();
	bool HasNewData() const;
	bool HasOverrun() const;
	bool IsCalibrated() const;

	int16_t GetRawX() const;
	int16_t GetRawY() const;
	int16_t GetRawZ() const;

	float GetX() const;
	float GetY() const;
	float GetZ() const;

private:
	FullScale mFullScale;
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
