#include "I2CSensorInterface.h"

I2CSensorInterface::I2CSensorInterface() :
	I2CSensorInterface(nullptr, 0x00)
{

}

I2CSensorInterface::I2CSensorInterface(rpi_i2c_t* i2c, uint8_t sAddr) :
	mSensorAddress(sAddr),
	mI2CBus(i2c == nullptr ? RPI_GetI2C1() : i2c)
{
}

I2CSensorInterface::I2CSensorInterface(uint8_t sAddr) :
	I2CSensorInterface(nullptr, sAddr)
{
}

void I2CSensorInterface::SetAddress(uint8_t addr)
{
	mSensorAddress = addr;
}

uint8_t I2CSensorInterface::ReadRegister8(uint8_t addr, uint8_t* data)
{
	uint8_t e = 0;
	e = mI2CBus->write(mSensorAddress, &addr, 1);
	if (e != 0)
		return e;
	return mI2CBus->read(mSensorAddress, data, 1);
}

uint8_t I2CSensorInterface::WriteRegister8(uint8_t addr, uint8_t data)
{
	uint8_t msg[2] = { addr, data };
	return mI2CBus->write(mSensorAddress, msg, 2);
}

uint8_t I2CSensorInterface::RequestFrom(uint8_t addr, uint8_t size, uint8_t* data)
{
	uint8_t e = 0;
	addr |= 1 << 7;
	e = mI2CBus->write(mSensorAddress, &addr, 1);
	if (e != 0)
		return e;

	return mI2CBus->read(mSensorAddress, data, size);
}
