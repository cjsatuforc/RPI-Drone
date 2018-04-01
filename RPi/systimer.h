#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#include "rpi-base.h"

#define RPI_SYSTIMER_BASE (PERIPHERAL_BASE + 0x3000UL)

	typedef struct
	{
		volatile uint32_t control_status;
		volatile uint32_t counter_lo;
		volatile uint32_t counter_hi;
		volatile uint32_t compare0;
		volatile uint32_t compare1;
		volatile uint32_t compare2;
		volatile uint32_t compare3;

		uint64_t counter() const
		{
			return uint64_t(counter_lo) | (uint64_t(counter_hi) << 32);
		}
	} rpi_sys_timer_t;

	extern rpi_sys_timer_t* RPI_GetSystemTimer(void);
	extern void RPI_WaitMicroSeconds(uint32_t us);

#ifdef __cplusplus
}
#endif
