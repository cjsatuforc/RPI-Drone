#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "rpi-base.h"

#define AUX_BASE (PERIPHERAL_BASE + 0x215000)

#define FSEL0(x) (x)
#define FSEL1(x) (x << 3)
#define FSEL2(x) (x << 6)
#define FSEL3(x) (x << 9)
#define FSEL4(x) (x << 12)
#define FSEL5(x) (x << 15)
#define FSEL6(x) (x << 18)
#define FSEL7(x) (x << 21)
#define FSEL8(x) (x << 24)
#define FSEL9(x) (x << 27)

#define FSEL10(x) (x)
#define FSEL11(x) (x << 3)
#define FSEL12(x) (x << 6)
#define FSEL13(x) (x << 9)
#define FSEL14(x) (x << 12)
#define FSEL15(x) (x << 15)
#define FSEL16(x) (x << 18)
#define FSEL17(x) (x << 21)
#define FSEL18(x) (x << 24)
#define FSEL19(x) (x << 27)

#define FSEL20(x) (x)
#define FSEL21(x) (x << 3)
#define FSEL22(x) (x << 6)
#define FSEL23(x) (x << 9)
#define FSEL24(x) (x << 12)
#define FSEL25(x) (x << 15)
#define FSEL26(x) (x << 18)
#define FSEL27(x) (x << 21)
#define FSEL28(x) (x << 24)
#define FSEL29(x) (x << 27)

#define FSEL30(x) (x)
#define FSEL31(x) (x << 3)
#define FSEL32(x) (x << 6)
#define FSEL33(x) (x << 9)
#define FSEL34(x) (x << 12)
#define FSEL35(x) (x << 15)
#define FSEL36(x) (x << 18)
#define FSEL37(x) (x << 21)
#define FSEL38(x) (x << 24)
#define FSEL39(x) (x << 27)

#define FSEL40(x) (x)
#define FSEL41(x) (x << 3)
#define FSEL42(x) (x << 6)
#define FSEL43(x) (x << 9)
#define FSEL44(x) (x << 12)
#define FSEL45(x) (x << 15)
#define FSEL46(x) (x << 18)
#define FSEL47(x) (x << 21)
#define FSEL48(x) (x << 24)
#define FSEL49(x) (x << 27)

#define FSEL50(x) (x)
#define FSEL51(x) (x << 3)
#define FSEL52(x) (x << 6)
#define FSEL53(x) (x << 9)

	typedef struct {
		union
		{
			struct
			{
				volatile unsigned int IRQ_MINIUART : 1,
					IRQ_SPI1 : 1,
					IRQ_SPI2 : 1,
					: 29;
			};
			volatile unsigned int IRQ;
		};

		union
		{
			struct
			{
				volatile unsigned int ENB_MINIUART : 1,
					ENB_SPI1 : 1,
					ENB_SPI2 : 1,
					: 29;
			};
			volatile unsigned int ENB;
		};

		volatile unsigned int RESERVED1[((0x40 - 0x04) / 4) - 1];

		union
		{
			union
			{
				volatile unsigned int MU_IO_LS8 : 8,
					MU_IO_TX : 8,
					MU_IO_RX : 8;
			};
			volatile unsigned int MU_IO;
		};

		union
		{
			struct
			{
				volatile unsigned int MU_IER_TX_IRQ : 1,
					MU_IER_RX_IRQ : 1,
					MU_IER_MSB : 6,
					: 24;
			};
			volatile unsigned int MU_IER;
		};

		union
		{
			struct
			{
				volatile unsigned int MU_IIR_IRQ_PENDING : 1,
					MU_IIR_R_IRQ_W_FIFO_CLEAR : 2,
					: 1,
					: 2,
					MU_IIR_FIFO_ENB : 2,
					: 24;
			};
			volatile unsigned int MU_IIR;
		};

		union
		{
			struct
			{
				volatile unsigned int MU_LCR_8BIT_MODE : 1,
					: 4,
					MU_LCR_BREAK : 1,
					MU_LCR_DLAB_ACCESS : 1,
					: 24;
			};
			volatile unsigned int MU_LCR;
		};

		union
		{
			struct
			{
				volatile unsigned int :1,
					MU_MCR_RTS : 1,
					: 6,
					: 24;
			};
			volatile unsigned int MU_MCR;
		};

		union
		{
			struct
			{
				volatile unsigned int MU_LSR_DATA_READY : 1,
					MU_LSR_RX_OVERRUN : 1,
					: 3,
					MU_LSR_TX_EMPTY : 1,
					MU_LSR_TX_IDLE : 1,
					: 1,
					: 24;
			};
			volatile unsigned int MU_LSR;
		};

		union
		{
			struct
			{
				volatile unsigned int : 5,
					MU_MSR_CTS_STATUS : 1,
					: 2,
					: 24;
			};
			volatile unsigned int MU_MSR;
		};

		volatile unsigned int MU_SCRATCH : 8,
			: 24;

		union
		{
			struct
			{
				volatile unsigned int MU_CNTL_RX_ENB : 1,
					MU_CNTL_TX_ENB : 1,
					MU_CNTL_RTS_FLOW : 1,
					MU_CNTL_CTS_FLOW : 1,
					MU_CNTL_RTS_FIFO : 2,
					MU_CNTL_RTS_ASSERT : 1,
					MU_CNTL_CTS_ASSERT : 1,
					: 24;
			};
			volatile unsigned int MU_CNTL;
		};

		union
		{
			struct
			{
				volatile unsigned int MU_STAT_SYMBOL_AV : 1,
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
			volatile unsigned int MU_STAT;
		};

		volatile unsigned int MU_BAUD : 16,
			: 16;

		volatile unsigned int RESERVED2[(0x80 - 0x68) / 4 - 1];

		union
		{
			struct
			{
				volatile unsigned int SPI1_CNTL0_SHIFT_LENGTH : 6,
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
			volatile unsigned int SPI1_CNTL0;
		};

		union
		{
			struct
			{

				volatile unsigned int SPI1_CNTL1_KEEP_INPUT : 1,
					SPI1_CNTL1_SHIFT_IN_MS_FIRST : 1,
					: 4,
					SPI1_CNTL1_DONE_IRQ : 1,
					SPI1_CNTL1_TX_EMPTY_IRQ : 1,
					SPI1_CNTL1_CS_HIGH : 3,
					: 21;
			};
			volatile unsigned int SPI1_CNTL1;
		};

		union
		{
			struct
			{
				volatile unsigned int SPI1_STAT_BIT_COUNT : 6,
					SPI1_STAT_BUSY : 1,
					SPI1_STAT_RX_EMPTY : 1,
					SPI1_STAT_TX_EMPTY : 1,
					SPI1_STAT_TX_FULL : 1,
					: 6,
					SPI1_STAT_RX_FIFO_LEVEL : 8,
					SPI1_STAT_TX_FIFO_LEVEL : 8;
			};
			volatile unsigned int SPI1_STAT;
		};

		volatile unsigned int RESERVED3[(0x90 - 0x88) / 4 - 1];

		volatile unsigned int SPI1_IO_DATA : 16,
			: 16;

		volatile unsigned int SPI1_PEEK_DATA : 16,
			: 16;

		volatile unsigned int RESERVED4[(0xC0 - 0x94) / 4 - 1];

		union
		{
			struct
			{
				volatile unsigned int SPI2_CNTL0_SHIFT_LENGTH : 6,
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
			volatile unsigned int SPI2_CNTL0;
		};

		union
		{
			struct
			{
				volatile unsigned int SPI2_CNTL1_KEEP_INPUT : 1,
					SPI2_CNTL1_SHIFT_IN_MS_FIRST : 1,
					: 4,
					SPI2_CNTL1_DONE_IRQ : 1,
					SPI2_CNTL1_TX_EMPTY_IRQ : 1,
					SPI2_CNTL1_CS_HIGH : 3,
					: 21;
			};
			volatile unsigned int SPI2_CNTL1;
		};

		union
		{
			struct
			{
				volatile unsigned int SPI2_STAT_BIT_COUNT : 6,
					SPI2_STAT_BUSY : 1,
					SPI2_STAT_RX_EMPTY : 1,
					SPI2_STAT_TX_EMPTY : 1,
					SPI2_STAT_TX_FULL : 1,
					: 6,
					SPI2_STAT_RX_FIFO_LEVEL : 8,
					SPI2_STAT_TX_FIFO_LEVEL : 8;
			};
			volatile unsigned int SPI2_STAT;
		};

		volatile unsigned int RESERVED5[(0xD0 - 0xC8) / 4 - 1];

		union
		{
			struct
			{
				volatile unsigned int SPI2_IO_DATA : 16,
					: 16;
			};
			volatile unsigned int SPI2_IO;
		};

		union
		{
			struct
			{
				volatile unsigned int SPI2_PEEK_DATA : 16,
					: 16;
			};
			volatile unsigned int SPI2_PEEK;
		};
	} rpi_aux_t;

	extern rpi_aux_t* RPI_GetAux(void);

	extern void RPI_AuxMiniUartInit(int baud, int bits);
	extern void RPI_AuxMiniUartWrite(char c);

	extern void RPI_AuxSPIInit(int channel, int baud);

#ifdef __cplusplus
}
#endif
