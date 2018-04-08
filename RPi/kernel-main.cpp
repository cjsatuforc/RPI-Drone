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

volatile extern bool calculate_frame_count;
volatile unsigned int tim;

void kernel_main(unsigned int r0, unsigned int r1, unsigned int atags)
{
	//*** GRAPHICS ***//

	RPI_SetGpioPinFunction(RPI_GPIO47, FS_OUTPUT);
	/*while (true)
	{
		RPI_SetGpioHi(RPI_GPIO47);
		RPI_WaitMicroSeconds(500000);

		RPI_SetGpioLo(RPI_GPIO47);
		RPI_WaitMicroSeconds(500000);
	}*/

	int width = SCREEN_WIDTH, height = SCREEN_HEIGHT, bpp = SCREEN_DEPTH, pitch = 0;
	float cd = COLOR_DELTA;
	unsigned int frame_count = 0;

	RPI_SetGpioPinFunction(RPI_GPIO47, FS_OUTPUT);

	
	//RPI_GetIrqController()->Enable_Basic_IRQs = RPI_BASIC_ARM_TIMER_IRQ;

	//RPI_GetArmTimer()->Load = 0x400;

	//RPI_GetArmTimer()->Control =
	//	RPI_ARMTIMER_CTRL_23BIT |
	//	RPI_ARMTIMER_CTRL_ENABLE |
	//	RPI_ARMTIMER_CTRL_INT_ENABLE |
	//	RPI_ARMTIMER_CTRL_PRESCALE_256;

	_enable_interrupts();

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
	
	//char text[8192];
	//for (int i = 0; i < 8192; i++)
	//	text[i] = 0;
	//RPI_SPI0Init();
	unsigned char v = 0;
	rpi_sys_timer_t* systimer = RPI_GetSystemTimer();
	RPI_I2C1Init();

	L3G4200D gyro;
	gyro.SetBandwidth(BWLow);
	gyro.SetHPFEnabled(false);
	gyro.SetLPFEnabled(true);
	gyro.SetFullScale(FS250);
	gyro.SetOutputDataRate(ODR800Hz);
	gyro.SetPower(true);
	gyro.Calibrate();

	uint32_t beginTime = systimer->counter_lo;
	uint32_t overrunCount = 0;
	while (true)
	{
		while (RPI_AuxMiniUartAvailable())
		{
			RPI_AuxMiniUartWrite(RPI_AuxMiniUartRead());
		}
		gyro.Tick();
		if (gyro.HasOverrun())
		{
			if (++overrunCount > 2)
			{
				printf("Gyro overrun!\r\n");
				RPI_SetGpioLo(RPI_GPIO47); //Turn LED on
			}
		}
		else
		{
			overrunCount = 0;
			RPI_SetGpioHi(RPI_GPIO47); //Turn LED off
		}
		//if (gyro.HasNewData())
		//	printf("%.1f     %.1f    %.1f\r\n", gyro.GetX(), gyro.GetY(), gyro.GetZ());

		if (systimer->counter_lo - beginTime >= 1000000)
		{
			//uint32_t t = systimer->counter_lo;
			//screen->clear();
			//
			printf("%u iterations per second\r\n", frame_count);

			frame_count = 0;
			beginTime = systimer->counter_lo;
		}

		++frame_count;
	}
}
