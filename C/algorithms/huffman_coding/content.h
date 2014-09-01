#ifndef __HEADER_H
#define __HEADER_H 1

#include <string.h>

#include "hash_table.h"
#include "huffman.h"

typedef struct len_struct {
    int l_char_map;
    int l_offset;
} l_struct;

void put_content(char *text, ht *char_map, FILE *file);

char *get_content(FILE *file);

#endif
