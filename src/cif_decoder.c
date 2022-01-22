#include "cif_decoder.h"

#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>

#include "utils.h"

void cif_decoder_init(CIF_Decoder *cif_decoder) {
	cif_decoder->input_path = NULL;
	cif_decoder->output_path = NULL;
	cif_decoder->dry_run = false;
}

bool cif_decoder_decode(CIF_Decoder *cif_decoder, CIF_File *cif_file) {
	FILE *file = fopen(cif_decoder->input_path, "rb");
	// Does this file exist?
	if (!file) {
		fprintf(stderr, "Input file not found or is not accessible \"%s\"\n", cif_decoder->input_path);
		return false;
	}

	// Find out how big is the file
	fseek(file, 0, SEEK_END);
	size_t file_size = ftell(file);
	fseek(file, 0, SEEK_SET);

	// Load the file into memory
	char *file_buffer = malloc(file_size + 1);
	fread(file_buffer, file_size, 1, file);
	fclose(file);
	file_buffer[file_size] = 0;

	fprintf(stderr, "Filesize: %ld KiB\n", file_size / 1024);

	// Check the file magic
	uint8_t magic_length = strlen(CIF_MAGIC);
	if (cif_compare(&file_buffer[0], CIF_MAGIC, magic_length) != 0) {
		fprintf(stderr, "Incorrect magic of the file, is it CIF file for sure?\n");
		return false;
	}

	// Lé main loopé
	for (size_t i = magic_length; i < file_size; ++i) {

	}

	// Free the memory
	free(file_buffer);

	return true;
}
