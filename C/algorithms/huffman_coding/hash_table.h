#ifndef __HASH_TABLE_H
#define __HASH_TABLE_H 1

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "hash_table.h"



#define LEAF_NODE(__c, __count, __code) ({  \
        ht *__t = (ht *)calloc(sizeof(ht), 1); \
        __t->c = __c;                            \
        __t->count = __count;                    \
        __t->code = __code;                    \
        __t->next = NULL;                      \
        __t->left = NULL;                      \
        __t->right = NULL;                      \
        __t;                                   \
        })

typedef struct __ht {
    char c;
    char *code;
    int count;
    struct __ht *left;
    struct __ht *right;
    struct __ht *next;
} ht;

ht *make_table(ht *head_ref, char *text);

void show_tree(ht *head_ref);

ht *get_min(ht **head_ref);

ht *add_node(ht **head_ref, ht *node);

size_t len_ht(ht *head_ref);

#endif
