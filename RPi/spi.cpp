#include "spi.h"
#include "gpio.h"

static rpi_spi0_t* spi0 = (rpi_spi0_t*)SPI0_BASE;

rpi_spi0_t* RPI_GetSPI0()
{
	return spi0;
}

void RPI_SPI0Init()
{
	RPI_SPI0Shutdown();

	RPI_SetGpioPinFunction(RPI_GPIO19, FS_ALT0);
	RPI_SetGpioPinFunction(RPI_GPIO21, FS_ALT0);
	RPI_SetGpioPinFunction(RPI_GPIO22, FS_ALT0);
	RPI_SetGpioPinFunction(RPI_GPIO23, FS_ALT0);
	RPI_SetGpioPinFunction(RPI_GPIO26, FS_ALT0);

	spi0->CS_CLEAR = 0b11;
	spi0->CS_INTD = 1;
	spi0->CS_INTR = 1;

	spi0->CS_CPOL = 0;
	spi0->CS_CPHA = 0;

	spi0->CS = 1;
	spi0->CS_CSPOL = 0;

	spi0->CLK_CDIV = 1024;
}

unsigned int RPI_SPI0Transfer(unsigned char val)
{
	unsigned int ret = 0;
	spi0->CS_CLEAR = 0b11;

	spi0->CS_TA = 1;

	while (!spi0->CS_TXD)
		;

	spi0->FIFO_REG = val;

	while (!spi0->CS_DONE)
		;

	ret = spi0->FIFO_REG;

	spi0->CS_TA = 0;

	return ret;
}

void RPI_SPI0Shutdown()
{
	RPI_SetGpioPinFunction(RPI_GPIO19, FS_INPUT);
	RPI_SetGpioPinFunction(RPI_GPIO21, FS_INPUT);
	RPI_SetGpioPinFunction(RPI_GPIO22, FS_INPUT);
	RPI_SetGpioPinFunction(RPI_GPIO23, FS_INPUT);
	RPI_SetGpioPinFunction(RPI_GPIO26, FS_INPUT);
}