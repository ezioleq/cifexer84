#ifndef CIF_DECODER_H
#define CIF_DECODER_H

#include <stdbool.h>

#include "cif_file.h"

// Supported flags
#define CIF_FLAG_POLISH "polish"

typedef enum CIF_ParsingState {
	CIF_STATE_FLAGS = 0,
	CIF_STATE_VERSION = 1,
	CIF_STATE_DIMENSIONS = 2,
	CIF_STATE_METADATA = 3,
	CIF_STATE_DATA = 4
} CIF_ParsingState;

typedef struct CIF_Decoder {
	CIF_ParsingState state;
	const char *input_path;
	const char *output_path;
	bool verbose;
	bool dry_run;
} CIF_Decoder;

void cif_decoder_init(CIF_Decoder *cif_decoder);
bool cif_decoder_decode(CIF_Decoder *cif_decoder, CIF_File *cif_file);

bool cif_decoder_parse_flag(const char *position, const char *flag);

#endif
