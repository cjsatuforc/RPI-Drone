#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "rpi-base.h"

#define AUX_BASE (PERIPHERAL_BASE + 0x215000)

	typedef struct {
		union
		{
			struct
			{
				rpi_reg_ro_t IRQ_MINIUART : 1,
					IRQ_SPI1 : 1,
					IRQ_SPI2 : 1,
					: 29;
			};
			rpi_reg_ro_t IRQ;
		};

		union
		{
			struct
			{
				rpi_reg_rw_t ENB_MINIUART : 1,
					ENB_SPI1 : 1,
					ENB_SPI2 : 1;
				rpi_reg_ro_t : 29;
			};
			rpi_reg_rw_t ENB;
		};

		rpi_reg_ro_t RESERVED1[((0x40 - 0x04) / 4) - 1];

		union
		{
			union
			{
				rpi_reg_rw_t MU_IO_LS8 : 8,
					MU_IO_TX : 8,
					MU_IO_RX : 8;
			};
			rpi_reg_rw_t MU_IO;
		};

		union
		{
			struct
			{
				rpi_reg_rw_t MU_IER_TX_IRQ : 1,
					MU_IER_RX_IRQ : 1,
					: 30;
			};
			struct
			{
				rpi_reg_rw_t MU_IER_MS8 : 8,
					: 24;
			};
			rpi_reg_rw_t MU_IER;
		};

		union
		{
			struct
			{
				rpi_reg_rw_t MU_IIR_IRQ_PENDING : 1,
					MU_IIR_R_IRQ_W_FIFO_CLEAR : 2,
					: 1,
					: 2,
					MU_IIR_FIFO_ENB : 2,
					: 24;
			};
			rpi_reg_rw_t MU_IIR;
		};

		union
		{
			struct
			{
				 rpi_reg_rw_t MU_LCR_8BIT_MODE : 1,
					: 5,
					MU_LCR_BREAK : 1,
					MU_LCR_DLAB_ACCESS : 1,
					: 24;
			};
			rpi_reg_rw_t MU_LCR;
		};

		union
		{
			struct
			{
				rpi_reg_rw_t : 1,
					MU_MCR_RTS : 1,
					: 6,
					: 24;
			};
			rpi_reg_rw_t MU_MCR;
		};

		union
		{
			struct
			{
				rpi_reg_ro_t MU_LSR_DATA_READY : 1,
					MU_LSR_RX_OVERRUN : 1,
					: 3,
					MU_LSR_TX_EMPTY : 1,
					MU_LSR_TX_IDLE : 1,
					: 1,
					: 24;
			};
			rpi_reg_ro_t MU_LSR;
		};

		union
		{
			struct
			{
				rpi_reg_ro_t : 5,
					MU_MSR_CTS_STATUS : 1,
					: 2,
					: 24;
			};
			rpi_reg_ro_t MU_MSR;
		};

		rpi_reg_rw_t MU_SCRATCH : 8,
			: 24;

		union
		{
			struct
			{
				rpi_reg_rw_t MU_CNTL_RX_ENB : 1,
					MU_CNTL_TX_ENB : 1,
					MU_CNTL_RTS_FLOW : 1,
					MU_CNTL_CTS_FLOW : 1,
					MU_CNTL_RTS_FIFO : 2,
					MU_CNTL_RTS_ASSERT : 1,
					MU_CNTL_CTS_ASSERT : 1,
					: 24;
			};
			rpi_reg_rw_t MU_CNTL;
		};

		union
		{
			struct
			{
				rpi_reg_ro_t MU_STAT_SYMBOL_AV : 1,
					MU_STAT_SPACE_AV : 1,
					MU_STAT_RX_IDLE : 1,
					MU_STAT_TX_IDLE : 1,
					MU_STAT_RX_OVERRUN : 1,
					MU_STAT_TX_FIFO_FULL : 1,
					MU_STAT_RTS : 1,
					MU_STAT_CTS : 1,
					MU_STAT_TX_EMPTY : 1,
					MU_STAT_TX_DONE : 1,
					: 6,
					MU_STAT_RX_FIFO_LEVEL : 4,
					: 4,
					MU_STAT_TX_FIFO_LEVEL : 4,
					: 4;
			};
			rpi_reg_ro_t MU_STAT;
		};

		rpi_reg_rw_t MU_BAUD : 16,
			: 16;

		rpi_reg_ro_t RESERVED2[(0x80 - 0x68) / 4 - 1];

		union
		{
			struct
			{
				rpi_reg_rw_t SPI1_CNTL0_SHIFT_LENGTH : 6,
					SPI1_CNTL0_SHIFT_OUT_MS_FIRST : 1,
					SPI1_CNTL0_INVERT_CLOCK : 1,
					SPI1_CNTL0_OUT_RISING : 1,
					SPI1_CNTL0_CLEAR_FIFOS : 1,
					SPI1_CNTL0_IN_RISING : 1,
					SPI1_CNTL0_ENB : 1,
					SPI1_CNTL0_DOUT_HOLD : 2,
					SPI1_CNTL0_VAR_WIDTH : 1,
					SPI1_CNTL0_VAR_CS : 1,
					SPI1_CNTL0_POST_INPUT : 1,
					SPI1_CNTL0_CS : 3,
					SPI1_CNTL0_SPEED : 12;
			};
			rpi_reg_rw_t SPI1_CNTL0;
		};

		union
		{
			struct
			{

				rpi_reg_rw_t SPI1_CNTL1_KEEP_INPUT : 1,
					SPI1_CNTL1_SHIFT_IN_MS_FIRST : 1,
					: 4,
					SPI1_CNTL1_DONE_IRQ : 1,
					SPI1_CNTL1_TX_EMPTY_IRQ : 1,
					SPI1_CNTL1_CS_HIGH : 3,
					: 21;
			};
			rpi_reg_rw_t SPI1_CNTL1;
		};

		union
		{
			struct
			{
				rpi_reg_rw_t SPI1_STAT_BIT_COUNT : 6,
					SPI1_STAT_BUSY : 1,
					SPI1_STAT_RX_EMPTY : 1,
					SPI1_STAT_TX_EMPTY : 1,
					SPI1_STAT_TX_FULL : 1,
					: 6,
					SPI1_STAT_RX_FIFO_LEVEL : 8,
					SPI1_STAT_TX_FIFO_LEVEL : 8;
			};
			rpi_reg_rw_t SPI1_STAT;
		};

		rpi_reg_ro_t RESERVED3[(0x90 - 0x88) / 4 - 1];

		rpi_reg_ro_t SPI1_IO_DATA : 16,
			: 16;

		rpi_reg_rw_t SPI1_PEEK_DATA : 16,
			: 16;

		rpi_reg_ro_t RESERVED4[(0xC0 - 0x94) / 4 - 1];

		union
		{
			struct
			{
				rpi_reg_rw_t SPI2_CNTL0_SHIFT_LENGTH : 6,
					SPI2_CNTL0_SHIFT_OUT_MS_FIRST : 1,
					SPI2_CNTL0_INVERT_CLOCK : 1,
					SPI2_CNTL0_OUT_RISING : 1,
					SPI2_CNTL0_CLEAR_FIFOS : 1,
					SPI2_CNTL0_IN_RISING : 1,
					SPI2_CNTL0_ENB : 1,
					SPI2_CNTL0_DOUT_HOLD : 2,
					SPI2_CNTL0_VAR_WIDTH : 1,
					SPI2_CNTL0_VAR_CS : 1,
					SPI2_CNTL0_POST_INPUT : 1,
					SPI2_CNTL0_CS : 3,
					SPI2_CNTL0_SPEED : 12;
			};
			rpi_reg_rw_t SPI2_CNTL0;
		};

		union
		{
			struct
			{
				rpi_reg_rw_t SPI2_CNTL1_KEEP_INPUT : 1,
					SPI2_CNTL1_SHIFT_IN_MS_FIRST : 1,
					: 4,
					SPI2_CNTL1_DONE_IRQ : 1,
					SPI2_CNTL1_TX_EMPTY_IRQ : 1,
					SPI2_CNTL1_CS_HIGH : 3,
					: 21;
			};
			rpi_reg_rw_t SPI2_CNTL1;
		};

		union
		{
			struct
			{
				rpi_reg_rw_t SPI2_STAT_BIT_COUNT : 6,
					SPI2_STAT_BUSY : 1,
					SPI2_STAT_RX_EMPTY : 1,
					SPI2_STAT_TX_EMPTY : 1,
					SPI2_STAT_TX_FULL : 1,
					: 6,
					SPI2_STAT_RX_FIFO_LEVEL : 8,
					SPI2_STAT_TX_FIFO_LEVEL : 8;
			};
			rpi_reg_rw_t SPI2_STAT;
		};

		rpi_reg_ro_t RESERVED5[(0xD0 - 0xC8) / 4 - 1];

		union
		{
			struct
			{
				rpi_reg_rw_t SPI2_IO_DATA : 16,
					: 16;
			};
			rpi_reg_rw_t SPI2_IO;
		};

		union
		{
			struct
			{
				rpi_reg_rw_t SPI2_PEEK_DATA : 16,
					: 16;
			};
			rpi_reg_rw_t SPI2_PEEK;
		};
	} rpi_aux_t;

	extern rpi_aux_t* RPI_GetAux(void);

	extern void RPI_AuxMiniUartInit(int baud, int bits);
	extern void RPI_AuxMiniUartWrite(char c);
	extern int RPI_AuxMiniUartRead();
	extern int RPI_AuxMiniUartAvailable();

	extern void RPI_AuxSPIInit(int channel, int baud);

#ifdef __cplusplus
}
#endif
