#include <stdint.h>
#include "armtimer.h"

static rpi_arm_timer_t* rpiArmTimer = (rpi_arm_timer_t*)RPI_ARMTIMER_BASE;

rpi_arm_timer_t* RPI_GetArmTimer()
{
	return rpiArmTimer;
}

void RPI_ArmTimerInit()
{

}