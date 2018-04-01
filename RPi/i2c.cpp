#include "i2c.h"
#include "gpio.h"

static rpi_i2c_t* i2c0 = (rpi_i2c_t*)I2C0_BASE;
static rpi_i2c_t* i2c1 = (rpi_i2c_t*)I2C1_BASE;
static rpi_i2c_t* i2c2 = (rpi_i2c_t*)I2C2_BASE;

rpi_i2c_t* RPI_GetI2C0()
{
	return i2c0;
}

rpi_i2c_t* RPI_GetI2C1()
{
	return i2c1;
}

rpi_i2c_t* RPI_GetI2C2()
{
	return i2c2;
}

void RPI_I2C0Init()
{
	RPI_I2C0Shutdown();
	rpi_i2c_t* i2c = RPI_GetI2C0();
	i2c->C_I2CEN = 1;
	i2c->C_CLEAR = 0b11;

	i2c->S_ERR = 1;
	i2c->S_CLKT = 1;
	i2c->S_DONE = 1;

	RPI_SetGpioPinFunction(RPI_GPIO2, FS_ALT0);
	RPI_SetGpioPinFunction(RPI_GPIO3, FS_ALT0);
}

void RPI_I2C1Init()
{
	RPI_I2C1Shutdown();
	rpi_i2c_t* i2c = RPI_GetI2C1();
	i2c->C_I2CEN = 1;
	i2c->C_CLEAR = 0b11;

	i2c->S_ERR = 1;
	i2c->S_CLKT = 1;
	i2c->S_DONE = 1;

	RPI_SetGpioPinFunction(RPI_GPIO2, FS_ALT0);
	RPI_SetGpioPinFunction(RPI_GPIO3, FS_ALT0);
}

void RPI_I2C2Init()
{
	RPI_I2C2Shutdown();
	rpi_i2c_t* i2c = RPI_GetI2C2();
	i2c->C_I2CEN = 1;
	i2c->C_CLEAR = 0b11;

	i2c->S_ERR = 1;
	i2c->S_CLKT = 1;
	i2c->S_DONE = 1;


}

void RPI_I2C0Shutdown()
{
	rpi_i2c_t* i2c = RPI_GetI2C0();
	i2c->C_I2CEN = 0;

	RPI_SetGpioPinFunction(RPI_GPIO2, FS_INPUT);
	RPI_SetGpioPinFunction(RPI_GPIO3, FS_INPUT);
}

void RPI_I2C1Shutdown()
{
	rpi_i2c_t* i2c = RPI_GetI2C1();
	i2c->C_I2CEN = 0;


}

void RPI_I2C2Shutdown()
{
	rpi_i2c_t* i2c = RPI_GetI2C2();
	i2c->C_I2CEN = 0;


}
