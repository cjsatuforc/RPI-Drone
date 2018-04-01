#pragma once

#include "definitions.h"

#ifdef __cplusplus
extern "C" {
#endif

#if defined(RPI2) || defined(RPI3)
#define PERIPHERAL_BASE 0x3F000000UL
#else
#define PERIPHERAL_BASE 0x20000000UL
#endif

#ifdef __cplusplus
}
#endif
