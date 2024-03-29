#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define NOT_IMPLEMENTED \
	fprintf(stderr, "Called function \"%s\" is not implemented!\n", __func__); \
	exit(126);

#ifdef __GNUC__
	#define ALWAYS_INLINE __attribute__((always_inline)) inline
#else
	#define ALWAYS_INLINE inline
#endif

ALWAYS_INLINE bool cif_compare(const char *a, const char *b, size_t len) {
	for (size_t i = 0; i < len; ++i) {
		if (a[i] != b[i])
			return false;
	}
	return true;
}

ALWAYS_INLINE bool cif_is_whitespace(char c) {
	return (c == ' ' || c == '\t');
}

#endif
