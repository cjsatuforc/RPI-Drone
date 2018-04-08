#pragma once

#include "i2c.h"

class I2CSensorInterface
{
public:
	I2CSensorInterface();
	I2CSensorInterface(rpi_i2c_t*, uint8_t sAddr);
	I2CSensorInterface(uint8_t sAddr);
	void SetAddress(uint8_t addr);
	uint8_t ReadRegister8(uint8_t addr, uint8_t* data);
	uint8_t WriteRegister8(uint8_t addr, uint8_t data);

private:
	uint8_t mSensorAddress;
	rpi_i2c_t* mI2CBus;
};
