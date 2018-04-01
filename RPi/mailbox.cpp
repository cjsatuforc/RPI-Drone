#include "gpio.h"
#include "mailbox.h"

static mailbox_t* rpiMailbox0 = (mailbox_t*)RPI_MAILBOX0_BASE;

void RPI_Mailbox0Write(mailbox0_channel_t channel, int value)
{
	value &= ~(0xF);
	value |= channel;

	while ((rpiMailbox0->Status & ARM_MS_FULL) != 0)
		;

	rpiMailbox0->Write = value;
}

int RPI_Mailbox0Read(mailbox0_channel_t channel)
{
	int value = -1;

	while ((value & 0xF) != channel)
	{
		while (rpiMailbox0->Status & ARM_MS_EMPTY)
			;
		value = rpiMailbox0->Read;
	}
	return value >> 4;
}