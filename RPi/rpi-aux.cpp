#include "rpi-aux.h"
#include "gpio.h"

static rpi_aux_t* auxillary = (rpi_aux_t*)AUX_BASE;

rpi_aux_t* RPI_GetAux()
{
	return auxillary;
}

#define SYS_FREQ 250000000

void RPI_AuxMiniUartInit(int baud, int bits)
{
	volatile int i;

	auxillary->ENB_MINIUART = 1;

	auxillary->MU_IER = 0;
	auxillary->MU_CNTL = 0;

	auxillary->MU_LCR = 3;
	
	auxillary->MU_MCR = 0;
	auxillary->MU_IER = 0;
	auxillary->MU_IIR = 0xC6;

	auxillary->MU_BAUD = (SYS_FREQ / (8 * baud)) - 1;

	RPI_SetGpioPinFunction(RPI_GPIO14, FS_ALT5);
	//RPI_SetGpioPinFunction(RPI_GPIO15, FS_ALT5);

	RPI_GetGpio()->GPPUD = 0;
	for (i = 0; i < 150; i++) {}
	RPI_GetGpio()->GPPUDCLK0 = (1 << 14);
	for (i = 0; i < 150; i++) {}
	RPI_GetGpio()->GPPUDCLK0 = 0;

	auxillary->MU_CNTL_TX_ENB = 1;
	auxillary->MU_CNTL_RX_ENB = 1;
}

void RPI_AuxMiniUartWrite(char c)
{
	while (!(auxillary->MU_LSR & 0x20))
		;

	auxillary->MU_IO = 0x30 + c;
	//auxillary->MU_IO_TX = c;
}

int RPI_AuxMiniUartRead()
{
	if (auxillary->MU_LCR_DLAB_ACCESS)
	{
		while (auxillary->MU_LSR_DATA_READY == 0)
			;
		return auxillary->MU_IO_RX;
	}
	return -1;
}
