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
#include <math.h>
#include <stdio.h>

volatile extern bool calculate_frame_count;
volatile unsigned int tim;

//template <typename T>
//void drawInt(unsigned int x, unsigned int y, T _n)
//{
//	int64_t n = _n;
//	char text[30];
//	for (unsigned int i = 0; i < 30; ++i)
//		text[i] = 0;
//
//	int idx = 0;
//	if (n < 0)
//		text[idx++] = '-';
//	n = n < 0 ? -n : n;
//	bool first = true;
//	for (unsigned int i = 29; i != -1; --i)
//	{
//		char c = '0' + ((n / (int64_t)(powf(10.0f, (float)i) + 0.5f)) % 10);
//		if (!first || c != '0')
//		{
//			first = false;
//			text[idx++] = c;
//		}
//	}
//
//	if (text[0] == 0)
//		text[0] = '0';
//
//	RPI_GetScreen()->drawText(x, y, text);
//}
//
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

	//_enable_interrupts();

	//RPI_AuxMiniUartInit(115200, 8);

	rpi_mailbox_property_t* mp;
	RPI_PropertyAddTag(TAG_GET_MAX_CLOCK_RATE, TAG_CLOCK_ARM);
	mp = RPI_PropertyGet(TAG_GET_MAX_CLOCK_RATE);
	
	/* Ensure the ARM is running at it's maximum rate */
	RPI_PropertyInit();
	RPI_PropertyAddTag(TAG_SET_CLOCK_RATE, TAG_CLOCK_ARM, mp->data.buffer_32[1]);
	RPI_PropertyProcess();

	//while (true)
	//{
	//	RPI_AuxMiniUartWrite('a');
	//	RPI_WaitMicroSeconds(1000000);
	//}

	rpi_screen_t* screen = RPI_GetScreen();
	screen->init(width, height, bpp, pitch);

	char message[64] = "Hello, World!";
	
	screen->setBackgroundColor(color32_t(200, 70, 255, 255));
	screen->setForegroundColor(color32_t(255, 255, 255, 255));
	
	//char text[8192];
	//for (int i = 0; i < 8192; i++)
	//	text[i] = 0;
	//RPI_SPI0Init();
	unsigned char v = 0;
	rpi_sys_timer_t* systimer = RPI_GetSystemTimer();
	uint32_t beginTime = systimer->counter_lo;
	RPI_I2C1Init();



	while (true)
	{
		if (systimer->counter_lo - beginTime >= 1000000)
		{
			screen->clear();
			printf("%i\n", frame_count);
			uint8_t whoami;
			rpi_i2c_t* i2c = RPI_GetI2C1();
			int e = 0;
			uint8_t reg = 0xF;
			i2c->write(0x69, &reg, 1);
			if ((e = i2c->read(0x69, &whoami, 1)) == 0)
			{
				printf("%u\n", whoami);
			}
			else
			{
				printf("%i\n", e);
			}
			
			frame_count = 0;
			beginTime = RPI_GetSystemTimer()->counter_lo;
		}

		++frame_count;
	}
}
