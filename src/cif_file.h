#ifndef CIF_FILE_H
#define CIF_FILE_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#define CIF_MAGIC "CIF:"
#define CIF_MAX_FLAGS 16

// Supported flags
#define CIF_FLAG_POLISH "polish"

// Different pixel sizes
typedef enum CIF_BitsPerPixel {
	CIF_BPP_24 = 24,
	CIF_BPP_32 = 32,
} CIF_BitsPerPixel;

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

// Representation of metadatum
typedef struct CIF_Metadatum {
	char *key;
	char *value;
} CIF_Metadatum;

// Representation of the CIF file
typedef struct CIF_File {
	// Magic, flags and version
	const char *magic;
	char **flags;
	size_t flags_length;
	uint32_t version;

	// Dimensions
	uint32_t width;
	uint32_t height;
	CIF_BitsPerPixel bpp;

	// Metadata
	CIF_Metadatum **metadata;
	size_t metadata_length;

	// Data
	void *pixel_data;
	size_t data_length;
} CIF_File;

bool cif_file_init(CIF_File *cif_file);
void cif_file_clean(CIF_File *cif_file);

bool cif_file_append_flag(CIF_File *cif_file, const char *flag);
bool cif_file_get_flag(CIF_File *cif_file, const char *flag);

#endif
