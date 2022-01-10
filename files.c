#include "duplicates.h"

// returns a OURFILE containing file's info
OURFILE *file_new(char *filepath, char *filename)
{
    // ensure file has enough memory allocated
    OURFILE *file = calloc(1, sizeof(OURFILE));
    CHECK_ALLOC(file);

    return file;
}