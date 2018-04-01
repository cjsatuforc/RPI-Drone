#include "armtimer.h"
#include "interrupts.h"
#include "rpi-base.h"
#include "gpio.h"
#include "definitions.h"
#include "systimer.h"

static rpi_irq_controller_t* rpiIRQController =
(rpi_irq_controller_t*)RPI_INTERRUPT_CONTROLLER_BASE;

volatile bool calculate_frame_count = false;

rpi_irq_controller_t* RPI_GetIrqController()
{
	return rpiIRQController;
}

extern "C"
{
	void PUT32(unsigned int, unsigned int);
	void reboot()
	{
		const int PM_RSTC = 0x3F10001c;
		const int PM_WDOG = 0x3F100024;
		const int PM_PASSWORD = 0x5a000000;
		const int PM_RSTC_WRCFG_FULL_RESET = 0x00000020;

		PUT32(PM_WDOG, PM_PASSWORD | 1);
		PUT32(PM_RSTC, PM_PASSWORD | PM_RSTC_WRCFG_FULL_RESET);
		while (1)
			;
	}

	void __attribute__((interrupt("ABORT"))) reset_vector()
	{
		while (true)
		{
			LED_ON();
			RPI_WaitMicroSeconds(200000);
			LED_OFF();
			RPI_WaitMicroSeconds(200000);
		}
	}

	void __attribute__((interrupt("UNDEF"))) undefined_instruction_vector()
	{
		while (true)
		{
			LED_ON();
			RPI_WaitMicroSeconds(200000);
			LED_OFF();
			RPI_WaitMicroSeconds(200000);
		}
	}

	void __attribute__((interrupt("SWI"))) software_interrupt_vector()
	{
		while (true)
		{
			LED_ON();
			RPI_WaitMicroSeconds(200000);
			LED_OFF();
			RPI_WaitMicroSeconds(200000);
		}
	}

	void __attribute__((interrupt("ABORT"))) prefetch_abort_vector()
	{
		while (true)
		{
			LED_ON();
			RPI_WaitMicroSeconds(200000);
			LED_OFF();
			RPI_WaitMicroSeconds(200000);
		}
	}

	void __attribute__((interrupt("ABORT"))) data_abort_vector()
	{
		while (true)
		{
			LED_ON();
			RPI_WaitMicroSeconds(200000);
			LED_OFF();
			RPI_WaitMicroSeconds(200000);
		}
	}

	void __attribute__((interrupt("IRQ"))) interrupt_vector()
	{
		static int ticks = 0;
		static int seconds = 0;
		static bool lit = false;
		RPI_GetArmTimer()->IRQClear = 1;
		if (!calculate_frame_count)
		{
			ticks++;
			if (ticks > 1)
			{
				ticks = 0;
				seconds++;
				if (seconds > 10)
				{
					seconds = 0;
					calculate_frame_count = true;

				}
			}
		}

		lit = !lit;
		RPI_SetGpioValue(RPI_GPIO47, lit ? RPI_IO_HI : RPI_IO_LO);
	}

	void __attribute__((interrupt("FIQ"))) fast_interrupt_vector()
	{
		while (true)
		{
			LED_ON();
			RPI_WaitMicroSeconds(200000);
			LED_OFF();
			RPI_WaitMicroSeconds(200000);
		}
	}
}
