#ifndef CIF_DECODER_H
#define CIF_DECODER_H

#include <stdbool.h>

#include "cif_file.h"

typedef struct CIF_Decoder {
	const char *input_path;
	const char *output_path;
	bool dry_run;
} CIF_Decoder;

void cif_decoder_init(CIF_Decoder *cif_decoder);
bool cif_decoder_decode(CIF_Decoder *cif_decoder, CIF_File *cif_file);

#endif
