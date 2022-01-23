#include "cif_file.h"

#include <string.h>

#include "utils.h"

bool cif_file_init(CIF_File *cif_file) {
	cif_file->magic = CIF_MAGIC;

	// Initialize flags array
	cif_file->flags = malloc(CIF_MAX_FLAGS * sizeof(char *));
	if (!cif_file->flags) {
		fprintf(stderr, "Cannot allocate memory for the flags array!");
		return false;
	}
	cif_file->flags_length = 0;

	cif_file->version = 0;

	// Dimensions
	cif_file->width = 0;
	cif_file->height = 0;
	cif_file->bpp = 0;

	// Initialize metadata array
	cif_file->metadata = NULL;
	cif_file->metadata_length = 0;

	// Initialize data fields
	cif_file->pixel_type = 0;
	cif_file->pixel_data = NULL;
	cif_file->data_length = 0;

	return true;
}

void cif_file_clean(CIF_File *cif_file) {
	// Free the flags
	for (size_t i = 0; i < cif_file->flags_length; ++i) {
		free(cif_file->flags[i]);
	}
	free(cif_file->flags);

	free(cif_file->metadata);
	free(cif_file->pixel_data);
}

bool cif_file_append_flag(CIF_File *cif_file, const char *flag) {
	// Do not exceed decoder flags limit
	if (cif_file->flags_length + 1 > CIF_MAX_FLAGS) {
		fprintf(stderr, "Max flags count exceeded, decoder limit is %d!\n", CIF_MAX_FLAGS);
		fprintf(stderr, "Ignoring \"%s\" flag...\n", flag);
		return false;
	}

	size_t flag_length = strlen(flag) + 1;
	size_t flags_count = cif_file->flags_length;

	// Allocate memory for the flag
	cif_file->flags[flags_count] = malloc(flag_length);

	// Allocation failed, return an error
	if (!cif_file->flags[flags_count]) {
		fprintf(stderr, "Cannot allocate memory for a flag!");
		return false;
	}

	// Copy the flag to the flags array
	memcpy(cif_file->flags[flags_count], flag, flag_length);
	++cif_file->flags_length;

	return true;
}

bool cif_file_get_flag(CIF_File *cif_file, const char *flag) {
	for (size_t i = cif_file->flags_length - 1; i; --i) {
		if (cif_compare(cif_file->flags[i], flag, strlen(flag)))
			return true;
	}

	return false;
}
