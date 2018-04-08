#include "i2c.h"
#include "gpio.h"
#include "systimer.h"

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

	const unsigned int f = 400000;
	i2c->DIV_CDIV = (((150000000 / f) + 1) & 0xFFFE);

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

uint8_t rpi_i2c_t::write(uint8_t addr, const uint8_t* data, uint32_t size)
{
	if (data == nullptr)
		return 1;
	uint16_t remaining = size;

	A_ADDR = addr;
	C_I2CEN = 1;
	C_CLEAR = 0b11;
	S_ERR = 1;
	S_CLKT = 1;
	S_DONE = 1;
	DLEN = size;
	int i = 0;

	C_READ = 0;
	C_ST = 1;
	while (!S_DONE)
	{
		while (remaining && S_TXD)
		{
			FIFO_DATA = data[i++];
			--remaining;
			RPI_WaitMicroSeconds(80);
		}
	}

	int ret = 0;
	if (S_ERR)
		ret = 2;
	else if (S_CLKT)
		ret = 3;
	else if (remaining)
	{
		ret = 4;
		C_CLEAR = 1;
	}
	
	S_ERR = 1;
	S_CLKT = 1;
	S_DONE = 1;

	return ret;
}

uint8_t rpi_i2c_t::read(uint8_t addr, uint8_t * data, uint32_t size)
{
	if (data == nullptr)
		return 1;
	uint16_t remaining = size;

	A_ADDR = addr;
	C_I2CEN = 1;
	C_CLEAR = 0b11;
	S_ERR = 1;
	S_CLKT = 1;
	S_DONE = 1;

	DLEN = size;

	C_READ = 1;
	C_ST = 1;
	int i = 0;
	while (!S_DONE)
	{
		if (remaining && S_RXD)
		{
			data[i++] = FIFO_DATA;
			--remaining;
		}
	}

	while (remaining && S_RXD)
	{
		data[i++] = FIFO_DATA;
		--remaining;
	}

	int ret = 0;
	if (S_ERR)
		ret = 2;
	else if (S_CLKT)
		ret = 3;
	else if (remaining)
		ret = 4;

	S_ERR = 1;
	S_CLKT = 1;
	S_DONE = 1;

	return ret;
}