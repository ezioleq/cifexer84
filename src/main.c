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

	if (!cif_decoder_decode(&decoder, &file)) {
		return 1;
	}

	// Print whole CIF file header
	{
		fprintf(stderr, "MAGIC: \"%s\"\n", CIF_MAGIC);
		fprintf(stderr, "FLAGS: [%ld]\n", file.flags_length);
		for (size_t i = 0; i < file.flags_length; ++i) {
			fprintf(stderr, "  FLAG: \"%s\"\n", file.flags[i]);
		}
		fprintf(stderr, "VERSION: %d\n", file.version);
		fprintf(stderr, "WIDTH: %d\n", file.width);
		fprintf(stderr, "HEIGTH: %d\n", file.height);
		fprintf(stderr, "BPP: %d\n", file.bpp);
		for (size_t i = 0;i < file.metadata_length; ++i) {
			// TODO: Print metadatums
			break;
		}
		fprintf(stderr, "DATA [%ld]\n", file.data_length);
	}

	cif_file_clean(&file);

	return 0;
}
