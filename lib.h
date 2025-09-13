#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define AVAILABLE_CHARACTERS 127
#define ENCODING_BITS 9

// TODO: TESTED, works well
char *matching_binary_string(char c);

// TODO: TESTED, works well
void *binary_encoder(char **sentence_buffer);

// TODO: TESTED, works well
FILE *file_optimizer(char *file_name);

FILE *encode_file(char *optimizedFile);
