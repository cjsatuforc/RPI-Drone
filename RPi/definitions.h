#pragma once

#ifdef __cplusplus
extern "C" {
#endif
#include <stdint.h>

#ifndef __GNUC__
#define __attribute__(A)
#define __extension__
#define _GLIBCXX_USE_C99 1
#define _HAVE_STDC 1
#endif

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define SCREEN_DEPTH 32

#define COLOR_DELTA 0.05

	typedef volatile uint32_t rpi_reg_rw_t;
	typedef volatile const uint32_t rpi_reg_ro_t;
	typedef volatile uint32_t rpi_reg_wo_t;

	typedef volatile uint64_t rpi_wreg_rw_t;
	typedef volatile const uint64_t rpi_wreg_ro_t;


#ifdef __cplusplus
}
#endif