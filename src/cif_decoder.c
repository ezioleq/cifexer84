#include "cif_decoder.h"

#include <stddef.h>

#include "utils.h"

void cif_decoder_init(CIF_Decoder *cif_decoder) {
	cif_decoder->input_path = NULL;
	cif_decoder->output_path = NULL;
	cif_decoder->dry_run = false;
}

void cif_decoder_decode(CIF_Decoder *cif_decoder, CIF_File *cif_file) {
	NOT_IMPLEMENTED
}
