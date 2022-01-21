#ifndef CIF_FILE_H
#define CIF_FILE_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#define CIF_MAGIC "CIF:"

// Different pixel sizes
typedef enum CIF_PixelType {
	CIF_BPP_24 = 24,
	CIF_BPP_32 = 32,
} CIF_PixelType;

// Representation of a 24-bit pixel
typedef struct CIF_Pixel24 {
	uint8_t r;
	uint8_t g;
	uint8_t b;
} CIF_Pixel24;

// Representation of a 32-bit pixel
typedef struct CIF_Pixel32 {
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;
} CIF_Pixel32;

// Representation of the CIF file
typedef struct CIF_File {
	// Magic, flags and version
	const char *magic;
	char *flags;
	size_t flags_length;
	uint32_t version;

	// Dimensions
	uint32_t width;
	uint32_t height;
	uint32_t bpp;

	// Metadata
	char *metadatas;
	size_t metadatas_length;

	// Data
	CIF_PixelType pixel_type;
	void *pixel_data;
	size_t data_length;

} CIF_File;

void cif_file_init(CIF_File *cif_file);
void cif_file_clean(CIF_File *cif_file);

#endif
