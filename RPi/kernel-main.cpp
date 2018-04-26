#include "gpio.h"
#include "systimer.h"
#include "armtimer.h"
#include "interrupts.h"
#include "mailbox.h"
#include "mailbox-interface.h"
#include "rpi-aux.h"
#include "screen.h"
#include "string.h"

#include "definitions.h"
#include "i2c.h"
#include "l3g4200d.h"
#include <math.h>
#include <stdio.h>

extern "C" void PUT32(unsigned int, unsigned int);
extern "C" unsigned int GET32(unsigned int);

void reboot()
{
	const int PM_RSTC = PERIPHERAL_BASE + 0x10001c;
	const int PM_WDOG = PERIPHERAL_BASE + 0x100024;
	const int PM_PASSWORD = 0x5a000000;
	const int PM_RSTC_WRCFG_FULL_RESET = 0x00000020;

	PUT32(PM_WDOG, PM_PASSWORD | 1);
	PUT32(PM_RSTC, PM_PASSWORD | PM_RSTC_WRCFG_FULL_RESET);
	while (1)
		;
}

void kernel_main(unsigned int r0, unsigned int r1, unsigned int atags)
{
	//*** GRAPHICS ***//

	/*RPI_SetGpioPinFunction(RPI_GPIO47, FS_OUTPUT);
	while (true)
	{
		RPI_SetGpioHi(RPI_GPIO47);
		RPI_WaitMicroSeconds(500000);

		RPI_SetGpioLo(RPI_GPIO47);
		RPI_WaitMicroSeconds(500000);
	}*/

	//int width = SCREEN_WIDTH, height = SCREEN_HEIGHT, bpp = SCREEN_DEPTH, pitch = 0;
	//float cd = COLOR_DELTA;
	unsigned int frame_count = 0;

	RPI_SetGpioPinFunction(RPI_GPIO47, FS_OUTPUT);

	//_enable_interrupts();

	RPI_AuxMiniUartInit(115200, 8);

	rpi_mailbox_property_t* mp;
	RPI_PropertyAddTag(TAG_GET_MAX_CLOCK_RATE, TAG_CLOCK_ARM);
	mp = RPI_PropertyGet(TAG_GET_MAX_CLOCK_RATE);
	
	/* Ensure the ARM is running at it's maximum rate */
	RPI_PropertyInit();
	RPI_PropertyAddTag(TAG_SET_CLOCK_RATE, TAG_CLOCK_ARM, mp->data.buffer_32[1]);
	RPI_PropertyProcess();

	//rpi_screen_t* screen = RPI_GetScreen();
	//screen->init(width, height, bpp, pitch);
	//
	//screen->setBackgroundColor(color32_t(200, 70, 255, 255));
	//screen->setForegroundColor(color32_t(255, 255, 255, 255));
	
	rpi_sys_timer_t* systimer = RPI_GetSystemTimer();
	RPI_I2C1Init();

	L3G4200D gyro;
	gyro.SetBandwidth(L3G4200D::BWLow);
	gyro.SetHPFEnabled(false);
	gyro.SetLPFEnabled(true);
	gyro.SetFullScale(L3G4200D::FS250);
	gyro.SetOutputDataRate(L3G4200D::ODR800Hz);
	gyro.SetPower(true);
	gyro.Calibrate();

	uint32_t lastFrameTime = systimer->counter_lo;
	uint32_t lastGyroTime = systimer->counter_lo;
	uint32_t overrunCount = 0;
	while (true)
	{
		while (RPI_AuxMiniUartAvailable())
		{
			if (RPI_AuxMiniUartRead() == 'r')
				reboot();
		}
		gyro.Tick();
		if (gyro.HasOverrun())
		{
			if (++overrunCount > 2)
			{
				//printf("Gyro overrun!\r\n");
				RPI_SetGpioLo(RPI_GPIO47); //Turn LED on
			}
		}
		else
		{
			overrunCount = 0;
			RPI_SetGpioHi(RPI_GPIO47); //Turn LED off
		}
		if (systimer->counter_lo - lastGyroTime >= 33333)
		{
			printf("%.1f     %.1f    %.1f\r\n", gyro.GetX(), gyro.GetY(), gyro.GetZ());
			lastGyroTime = systimer->counter_lo;
		}

		if (systimer->counter_lo - lastFrameTime >= 1000000)
		{
			printf("%u iterations per second\r\n", frame_count);

			frame_count = 0;
			lastFrameTime = systimer->counter_lo;
		}

		++frame_count;
	}
}
