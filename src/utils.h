#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>

#define NOT_IMPLEMENTED \
	fprintf(stderr, "Called function \"%s\" is not implemented!\n", __func__); \
	exit(126);

#ifdef __GNUC__
	#define ALWAYS_INLINE __attribute__((always_inline)) inline
#else
	#define ALWAYS_INLINE inline
#endif

#endif
