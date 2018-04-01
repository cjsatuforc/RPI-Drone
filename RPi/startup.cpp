extern int __bss_start__; //defined by linker
extern int __bss_end__; //defined by linker

extern void kernel_main(unsigned int r0, unsigned int r1, unsigned int atags);

extern "C"
{
	void _clearBssSection()
	{
		int* bss = &__bss_start__;
		int* bss_end = &__bss_end__;

		while (bss < bss_end) //Set .bss section to 0
			*bss++ = 0;
	}

	void _cstartup(unsigned int r0, unsigned int r1, unsigned int r2)
	{
		_clearBssSection();
		kernel_main(r0, r1, r2); //start execution, never return

		while (true)
			;
	}

}