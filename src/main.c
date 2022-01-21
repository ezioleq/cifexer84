#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "cif_file.h"
#include "cif_decoder.h"

int main(int argc, char* argv[]) {
	CIF_Decoder decoder;
	cif_decoder_init(&decoder);

	// Arguments check
	if (argc < 3) {
		// Fancy help message
		fprintf(stderr, "cifexer84 [%d] : Ezioleq 2022 : %s\n", __LINE__, __DATE__);
		fprintf(stderr, "Usage: cifexer84 <input.cif> <output.bmp> [OPTION]...\n");
		fprintf(stderr, "\n");
		fprintf(stderr, "  --dry-run        Do not save the result\n");

		return 1;
	} else if (argc >= 3) {
		// Set input file and output file
		decoder.input_path = argv[1];
		decoder.output_path = argv[2];

		// Very lazy way of parsing rest of the arguments
		if (argc > 3) {
			for (size_t i = 2; i < argc; ++i) {
				if (strcmp(argv[i], "--dry-run") == 0)
					decoder.dry_run = true;
			}
		}
	}

	CIF_File file;
	cif_file_init(&file);

	cif_decoder_decode(&decoder, &file);

	cif_file_clean(&file);

	return 0;
}
