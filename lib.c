#include "lib.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *matching_binary_string(char c) {
  bool is_present;

  char available_characters[AVAILABLE_CHARACTERS] = {
      'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h',  'i', 'j',
      'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r',  's', 't',
      'u', 'v', 'w', 'x', 'y', 'z', ' ', '\n', ',',
  };
  static char list[AVAILABLE_CHARACTERS][ENCODING_BITS] = {
      ['a'] = {'0', '1', '1', '0', '0', '0', '0', '1', '\0'},
      ['b'] = {'0', '1', '1', '0', '0', '0', '1', '0', '\0'},
      ['c'] = {'0', '1', '1', '0', '0', '0', '1', '1', '\0'},
      ['d'] = {'0', '1', '1', '0', '0', '1', '0', '0', '\0'},
      ['e'] = {'0', '1', '1', '0', '0', '1', '0', '1', '\0'},
      ['f'] = {'0', '1', '1', '0', '0', '1', '1', '0', '\0'},
      ['g'] = {'0', '1', '1', '0', '0', '1', '1', '1', '\0'},
      ['h'] = {'0', '1', '1', '0', '1', '0', '0', '0', '\0'},
      ['i'] = {'0', '1', '1', '0', '1', '0', '0', '1', '\0'},
      ['j'] = {'0', '1', '1', '0', '1', '0', '1', '0', '\0'},
      ['k'] = {'0', '1', '1', '0', '1', '0', '1', '1', '\0'},
      ['l'] = {'0', '1', '1', '0', '1', '1', '0', '0', '\0'},
      ['m'] = {'0', '1', '1', '0', '1', '1', '0', '1', '\0'},
      ['n'] = {'0', '1', '1', '0', '1', '1', '1', '0', '\0'},
      ['o'] = {'0', '1', '1', '0', '1', '1', '1', '1', '\0'},
      ['p'] = {'0', '1', '1', '1', '0', '0', '0', '0', '\0'},
      ['q'] = {'0', '1', '1', '1', '0', '0', '0', '1', '\0'},
      ['r'] = {'0', '1', '1', '1', '0', '0', '1', '0', '\0'},
      ['s'] = {'0', '1', '1', '1', '0', '0', '1', '1', '\0'},
      ['t'] = {'0', '1', '1', '1', '0', '1', '0', '0', '\0'},
      ['u'] = {'0', '1', '1', '1', '0', '1', '0', '1', '\0'},
      ['v'] = {'0', '1', '1', '1', '0', '1', '1', '0', '\0'},
      ['w'] = {'0', '1', '1', '1', '0', '1', '1', '1', '\0'},
      ['x'] = {'0', '1', '1', '1', '1', '0', '0', '0', '\0'},
      ['y'] = {'0', '1', '1', '1', '1', '0', '0', '1', '\0'},
      ['z'] = {'0', '1', '1', '1', '1', '0', '1', '0', '\0'},
      [' '] = {'0', '0', '1', '0', '0', '0', '0', '0', '\0'},
      ['\n'] = {'0', '1', '1', '1', '1', '1', '0', '0', '\0'},
      [','] = {'0', '1', '1', '1', '1', '1', '0', '1', '\0'},
  };

  for (int i = 0; i < AVAILABLE_CHARACTERS; i++) {
    if (c == available_characters[i]) {
      is_present = true;
      break;
    } else {
      is_present = false;
    }
  }
  if (is_present == true)
    return list[c];
  else
    return NULL;
};

void *binary_encoder(char **sentence_buffer) {
  // REMEBER : dealing with file line
  size_t sentence_buffer_size;
  char *buff;

  char *og_sentence = *sentence_buffer;

  sentence_buffer_size = ENCODING_BITS * strlen(*sentence_buffer);
  buff = malloc(sentence_buffer_size + 1);
  if (buff == NULL) {
    return NULL;
  }

  for (int i = 0; i < strlen(*sentence_buffer); i++) {
    char *byte = NULL;
    while (byte == NULL) {
      byte = matching_binary_string(og_sentence[i]);
      if (byte == NULL) {
        fprintf(stderr, "Character (%c) not supported\n", og_sentence[i]);
        free(buff);
        return NULL;
      }
    }
    strncat(buff, byte, strlen(byte));
    strncat(buff, " ", 2);
  }
  buff[sentence_buffer_size] = '\0';

  return buff;
}

FILE *file_optimizer(char *file_name) {
  size_t size = 1024;
  FILE *fptr;
  FILE *optimizedFile;

  char *buff = malloc(size);
  if (buff == NULL) {
    return NULL;
  }

  fptr = fopen(file_name, "r");            // source file
  optimizedFile = fopen("optimized", "w"); // optimized file

  if (fptr == NULL || optimizedFile == NULL) {
    free(buff);
    return NULL;
  }

  while ((fgets(buff, 1024, fptr)) != NULL) {
    if (strlen(buff) > 1) {
      fprintf(optimizedFile, "%s", buff);
      memset(buff, 0, size);
    }
  }
  free(buff);
  buff = NULL;
  fclose(fptr);

  return optimizedFile;
}

FILE *encode_file(char *optimized_file_name) {
  char *buff;
  FILE *encoded_file;
  FILE *optimized_file;

  encoded_file = fopen("encoded.bin", "w");
  optimized_file = fopen(optimized_file_name, "r");

  if (optimized_file == NULL || encoded_file == NULL) {
    fprintf(stderr, "Provided file is null\n");
    fclose(optimized_file);
    fclose(encoded_file);

    return NULL;
  }

  buff = malloc(1024);
  if (buff == NULL) {
    fclose(optimized_file);
    fclose(encoded_file);

    return NULL;
  }

  while ((fgets(buff, 1024, optimized_file)) != NULL) {
    char *temp = binary_encoder(&buff);
    fprintf(encoded_file, "%s", temp);
    memset(buff, 0, 1024);
  }

  fclose(optimized_file);
  return encoded_file;
}
