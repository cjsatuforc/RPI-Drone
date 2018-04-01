#pragma once

#include "rpi-base.h"
#include "definitions.h"

#define SPI0_BASE (PERIPHERAL_BASE + 0x204000)

typedef struct
{
	union
	{
		struct
		{
			rpi_reg_rw_t CS : 2;
			rpi_reg_rw_t CS_CPHA : 1;
			rpi_reg_rw_t CS_CPOL : 1;
			rpi_reg_rw_t CS_CLEAR : 2;
			rpi_reg_rw_t CS_CSPOL : 1;
			rpi_reg_rw_t CS_TA : 1;
			rpi_reg_rw_t CS_DMAEN : 1;
			rpi_reg_rw_t CS_INTD : 1;
			rpi_reg_rw_t CS_INTR : 1;
			rpi_reg_rw_t CS_ADCS : 1;
			rpi_reg_rw_t CS_REN : 1;
			rpi_reg_rw_t CS_LEN : 1;
			rpi_reg_rw_t CS_LMONO : 1;
			rpi_reg_rw_t CS_TE_EN : 1;
			rpi_reg_ro_t CS_DONE : 1;
			rpi_reg_ro_t CS_RXD : 1;
			rpi_reg_ro_t CS_TXD : 1;
			rpi_reg_ro_t CS_RXR : 1;
			rpi_reg_ro_t CS_RXF : 1;
			rpi_reg_rw_t CS_CSPOL0 : 1;
			rpi_reg_rw_t CS_CSPOL1 : 1;
			rpi_reg_rw_t CS_CSPOL2 : 1;
			rpi_reg_rw_t CS_DMA_LEN : 1;
			rpi_reg_rw_t CS_LEN_LONG : 1;
			rpi_reg_rw_t : 6;
		};
		rpi_reg_rw_t CS_REG;
	};

	union
	{
		struct
		{
			rpi_reg_rw_t FIFO_DATA : 32;
		};
		rpi_reg_rw_t FIFO_REG;
	};

	union
	{
		struct
		{
			rpi_reg_rw_t CLK_CDIV : 16,
				: 16;
		};
		rpi_reg_rw_t CLK_REG;
	};

	union
	{
		struct
		{
			rpi_reg_rw_t DLEN_LEN : 16,
				: 16;
		};
		rpi_reg_rw_t DLEN_REG;
	};

	union
	{
		struct
		{
			rpi_reg_rw_t LTOH_TOH : 4,
				: 28;
		};
		rpi_reg_rw_t LTOH_REG;
	};

	union
	{
		struct
		{
			rpi_reg_rw_t DC_TDREQ : 8,
				DC_TPANIC : 8,
				DC_RDREQ : 8,
				DC_RPANIC : 8;
		};
		rpi_reg_rw_t DC_REG;
	};
} rpi_spi0_t;

rpi_spi0_t* RPI_GetSPI0();
void RPI_SPI0Init();
unsigned int RPI_SPI0Transfer(unsigned char val);
void RPI_SPI0Shutdown();