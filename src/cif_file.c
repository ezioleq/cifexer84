#include "cif_file.h"

#include "utils.h"

void cif_file_init(CIF_File *cif_file) {
	cif_file->magic = CIF_MAGIC;
	cif_file->flags = NULL;
	cif_file->flags_length = 0;
	cif_file->version = 0;

	cif_file->width = 0;
	cif_file->height = 0;
	cif_file->bpp = 0;

	cif_file->metadatas = NULL;
	cif_file->metadatas_length = 0;

	cif_file->pixel_type = 0;
	cif_file->pixel_data = NULL;
	cif_file->data_length = 0;
}

void cif_file_clean(CIF_File *cif_file) {
	free(cif_file->flags);
	free(cif_file->metadatas);
	free(cif_file->pixel_data);
}
