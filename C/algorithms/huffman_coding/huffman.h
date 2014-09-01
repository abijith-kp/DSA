#ifndef __HUFFMAN_H
#define __HUFFMAN_H 1

#include <string.h>
#include <stdlib.h>

#include "hash_table.h"

ht *prefix_code(ht *head_ref, char *symbol, ht **char_map);

char *get_code(char c, ht *char_map);

#endif
