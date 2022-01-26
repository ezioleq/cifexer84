#include "cif_decoder.h"

#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>

#include "utils.h"

void cif_decoder_init(CIF_Decoder *cif_decoder) {
	cif_decoder->state = CIF_STATE_FLAGS;
	cif_decoder->input_path = NULL;
	cif_decoder->output_path = NULL;
	cif_decoder->verbose = false;
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

	if (cif_decoder->verbose)
		fprintf(stderr, "FILE SIZE: %ld KiB\n", file_size / 1024);

	// Check the file magic
	uint8_t magic_length = strlen(CIF_MAGIC);
	if (!cif_compare(&file_buffer[0], CIF_MAGIC, magic_length)) {
		fprintf(stderr, "Incorrect magic of the file, is it CIF file for sure?\n");
		return false;
	}

	// Lé main loopé
	for (size_t i = magic_length; i < file_size; ++i) {
		char byte = file_buffer[i];
		// Ignore all whitespace
		if (cif_is_whitespace(byte))
			continue;

		// The plan is to move everything related to the CIF header outside this loop
		// so it won't be computed every iteration. Just data parsing state should be here.
		// TODO: Move header parsing outside the main loop.
		// But the question is: Will this branch of switch cases be that slow?

		// This crazy state checking is my idea to make my life easier by separating some
		// parts of the code which can be specific to single CIF line i.e. flags parsing,
		// dimensions or metadata.
		switch (cif_decoder->state) {
			case CIF_STATE_FLAGS: {
				if (cif_decoder_parse_flag(file_buffer + i, CIF_FLAG_POLISH)) {
					cif_file_append_flag(cif_file, CIF_FLAG_POLISH);
				}

				if (byte == '\n')
					cif_decoder->state++;
				break;
			}
			case CIF_STATE_VERSION:
				break;
			case CIF_STATE_DIMENSIONS:
				break;
			case CIF_STATE_METADATA:
				break;
			case CIF_STATE_DATA:
				break;
		}
	}

	// Free the memory
	free(file_buffer);

	return true;
}

bool cif_decoder_parse_flag(const char *position, const char *flag) {
	size_t flag_length = strlen(flag);
	char byte = *(position + flag_length);

	// According to The Paper™ flags are defined as:
	// flags <- flag (',' ws flag)*
	// So if there is more than one flag they must by separated by exact one
	// comma and any number of whitespace characters, this monstrosity is
	// checking for existance of the comma and following whitespace.
	// Another hand, if the next character is a line feed it's okay.
	// We will skip the fact, that the standard defines only one flag,
	// which is "polish".

	if (cif_compare(position, flag, flag_length)) {
		if ((byte == ',' && cif_is_whitespace(*(position + flag_length + 1))) || byte == '\n')
			return true;
	}

	return false;
}
