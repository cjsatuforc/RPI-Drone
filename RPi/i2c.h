#pragma once

#include "definitions.h"
#include "rpi-base.h"

#define I2C0_BASE (PERIPHERAL_BASE + 0x205000)
#define I2C1_BASE (PERIPHERAL_BASE + 0x804000)
#define I2C2_BASE (PERIPHERAL_BASE + 0x805000)

typedef struct
{
	union
	{
		struct
		{
			rpi_reg_rw_t C_READ : 1,
				: 3,
				C_CLEAR : 2,
				: 1,
				C_ST : 1,
				C_INTD : 1,
				C_INTT : 1,
				C_INTR : 1,
				: 4,
				C_I2CEN : 1,
				: 16;
		};
		rpi_reg_rw_t C_REG;
	};

	union
	{
		struct
		{
			rpi_reg_ro_t S_TA : 1;
			rpi_reg_rw_t S_DONE : 1;
			rpi_reg_ro_t S_TXW : 1,
				S_RXR : 1,
				S_TXD : 1,
				S_RXD : 1,
				S_TXE : 1,
				S_RXF : 1;
			rpi_reg_rw_t S_ERR : 1,
				S_CLKT : 1;
			rpi_reg_ro_t : 22;
		};
		rpi_reg_rw_t S_REG;
	};

	union
	{
		struct
		{
			rpi_reg_rw_t DLEN : 16;
			rpi_reg_ro_t : 16;
		};
		rpi_reg_rw_t DLEN_REG;
	};

	union
	{
		struct
		{
			rpi_reg_rw_t A_ADDR : 7;
			rpi_reg_ro_t : 25;
		};
		rpi_reg_rw_t A_REG;
	};

	union
	{
		struct
		{
			rpi_reg_rw_t FIFO_DATA : 8;
			rpi_reg_ro_t : 24;
		};
		rpi_reg_rw_t FIFO_REG;
	};

	union
	{
		struct
		{
			rpi_reg_rw_t DIV_CDIV : 16;
			rpi_reg_ro_t : 16;
		};
		rpi_reg_rw_t DIV_REG;
	};

	union
	{
		struct
		{
			rpi_reg_rw_t DEL_REDL : 16,
				DEL_FEDL : 16;
		};
		rpi_reg_rw_t DEL_REG;
	};

	union
	{
		struct
		{
			rpi_reg_rw_t CLKT_TOUT : 16;
			rpi_reg_ro_t : 16;
		};
		rpi_reg_rw_t CLKT_REG;
	};

	//Returns: error code
	//0: no error
	//1: data == nullptr
	//2: NACK
	//3: timeout
	//4: not all bytes written?
	uint8_t write(uint8_t addr, const uint8_t* data, uint32_t size)
	{
		if (data == nullptr)
			return 1;
		uint16_t remaining = size;

		A_ADDR = addr;
		C_CLEAR = 1;
		S_ERR = 1;
		S_CLKT = 1;
		S_DONE = 1;
		DLEN = size;

		int i = 0;
		while (remaining && (i < 16)) {
			FIFO_DATA = data[i++];
			--remaining;
		}

		C_ST = 1;
		while (!S_DONE)
		{
			if (remaining && S_TXD)
			{
				FIFO_DATA = data[i++];
				--remaining;
			}
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

	//Returns error code or number of bytes read
	//0: no error
	//1: data == nullptr
	//2: NACK
	//3: timeout
	//4: not all bytes read?
	uint8_t read(uint8_t addr, uint8_t* data, uint32_t size)
	{
		if (data == nullptr)
			return 1;
		uint16_t remaining = size;
		
		A_ADDR = addr;
		C_CLEAR = 1;
		S_ERR = 1;
		S_CLKT = 1;
		S_DONE = 1;

		DLEN = size;

		//C_REG = (1 << 15) | (1 << 7) | (1 << 0);
		C_READ = 1;
		C_ST = 1;
		int i = 0;
		while (!S_DONE)
		{
			if (S_RXD)
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

} rpi_i2c_t;

rpi_i2c_t* RPI_GetI2C0();
rpi_i2c_t* RPI_GetI2C1();
rpi_i2c_t* RPI_GetI2C2();

void RPI_I2C0Init();
void RPI_I2C1Init();
void RPI_I2C2Init();

void RPI_I2C0Shutdown();
void RPI_I2C1Shutdown();
void RPI_I2C2Shutdown();



