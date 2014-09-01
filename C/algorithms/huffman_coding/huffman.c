#include "huffman.h"

ht *prefix_code(ht *head_ref, char *symbol, ht **char_map) {
    char *t;
    if(!symbol)
        symbol = "";
    if(head_ref->left) {
        t = (char *)calloc(sizeof(char), strlen(symbol)+1);
        sprintf(t, "%s0", symbol);
        prefix_code(head_ref->left, t, char_map);
    }
    if(!head_ref->left && !head_ref->right) {
        head_ref->code = symbol;
        ht *node = LEAF_NODE(head_ref->c, head_ref->count, symbol);
        *char_map = add_node(char_map, node);
        return *char_map;
    }
    if(head_ref->right) {
        t = (char *)calloc(sizeof(char), strlen(symbol)+1);
        sprintf(t, "%s1", symbol);
        prefix_code(head_ref->right, t, char_map);
    }

    return *char_map;
}

char *get_code(char c, ht *char_map) {
    while(char_map) {
        if(char_map->c == c)
            return char_map->code;
        char_map = char_map->next;
    }
    return NULL;
}
