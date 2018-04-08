#pragma once

#include "I2CSensorInterface.h"

enum LSM303DLHCAccelFullScale
{
	FS2G = 0b00,
	FS4G = 0b01,
	FS8G = 0b10,
	FS16G = 0b11
};

enum LSM303DLHCMagnetoFullScale
{

};

class LSM303DLHC : public I2CSensorInterface
{
public:
	LSM303DLHC();
	LSM303DLHC(const LSM303DLHC& other) = delete;
	LSM303DLHC(LSM303DLHC&& other) = delete;

	void SetAccelFullScale(LSM303DLHCAccelFullScale FS);
	void SetMagnetoFullScale(LSM303DLHCMagnetoFullScale FS);

	void Calibrate();
	void Tick();


};
