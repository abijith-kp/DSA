#include "content.h"
#include <stdio.h>

void put_content(char *text, ht *char_map, FILE *file) {
    char c, storage_bit[9], char_bits=0, x, *code, c_str[2]={'\0'},
         *write_text=NULL;
    int cur_bit=7, pos=0, len, l_char_map=0, l_offset=0;
    ht *t_char_map;

#   ifdef __TEST
    char __test_buffer[9];
#   endif

    l_char_map = len_ht(char_map);

    write_text = (char *)calloc(sizeof(char), 0);
    while(*text != '\0') {
        x = *text;
        code = get_code(x, char_map);
        if(code == NULL) {
            fprintf(stderr, "Undected character. Aborting.%c\n", x);
            exit(1);
        }

        while(*code != '\0') {
            c = *code;
#           ifdef __TEST
            __test_buffer[7-cur_bit] = c;
#           else
            if(c == '1')
                char_bits |= (1<<cur_bit);
#           endif
            cur_bit--;
            if(cur_bit == -1) {
#               ifdef __TEST
                __test_buffer[8] = '\0';
                write_text = (char *)realloc(write_text, strlen(write_text)+strlen(__test_buffer));
                strcat(write_text, __test_buffer);
                memset(&__test_buffer, 0, 9*sizeof(char));
#               else
                write_text = (char *)realloc(write_text, strlen(write_text)+2);
                strncat(write_text, &char_bits, 1);
                memset(&storage_bit, 0, 9*sizeof(char));
#               endif
                cur_bit = 7;
                char_bits = 0;
                pos = 0;
                storage_bit[pos++] = x;
            }
            code++;
        }
        text++;
    }
    storage_bit[pos++] = '\0';
    l_offset = (int)strlen(write_text);

    fwrite((void *)&l_char_map, sizeof(int), 1, file);
    fwrite((void *)&l_offset, sizeof(int), 1, file);

#   ifdef __TEST
    file = stdout;
#   endif

    t_char_map = char_map;
    while(t_char_map) {
        c = t_char_map->c;
        c_str[0] = c;
        c_str[1] = '\0';
        len = t_char_map->count;
        fwrite((void *)&c_str, sizeof(char), 2, file);
        fwrite((void *)&len, sizeof(int), 1, file);
        t_char_map = t_char_map->next;
    }

    write_text = (char *)realloc(write_text, strlen(write_text)+pos);
    strcat(write_text, storage_bit);
    fwrite((void *)write_text, sizeof(char), strlen(write_text), file);
}

char *get_content(FILE *file) {
    char c, x;
    int i=0, len=0, l_char_map=0, l_offset=0, count=0;
    char *t_text=NULL, c_str[2];
    ht *char_map=NULL, *t=NULL, *hash_table=NULL, *node1, *node2, *state=NULL;

    memset(&c_str, 0, sizeof(c_str));

    fread((void *)&l_char_map, sizeof(int), 1, file);
    fread((void *)&l_offset, sizeof(int), 1, file);

#   ifdef __TEST1
    fwrite((void *)&l_char_map, sizeof(int), 1, stdout);
    fwrite((void *)&l_offset, sizeof(int), 1, stdout);
#   endif

    for(i=0; i<l_char_map; i++) {
        fread((void *)&c_str, sizeof(char), 2, file);
        fread((void *)&len, sizeof(int), 1, file);
#   ifdef __TEST
        fwrite((void *)&c_str, sizeof(char), 2, stdout);
        fwrite((void *)&len, sizeof(int), 1, stdout);
#   endif
        t = LEAF_NODE(c_str[0], len, NULL);
        hash_table = add_node(&hash_table, t);
    }

    for(len=len_ht(hash_table); len>1; len=len_ht(hash_table)) {
        node1 = get_min(&hash_table);
        node2 = get_min(&hash_table);
        t = LEAF_NODE(' ', (node1->count + node2->count), 0);
        if(node1->count < node2->count) {
            t->left = node1;
            t->right = node2;
        }
        else {
            t->left = node2;
            t->right = node1;
        }
        hash_table = add_node(&hash_table, t);
    }
    char_map = prefix_code(hash_table, NULL, &char_map);

#   if (defined __TEST ) && (defined __TABLE)
    show_tree(hash_table);
    printf("\n\n");
#   endif

    /* make use of l_offset here in decoding */
    t_text = (char *)calloc(sizeof(char), 1);
    memset(t_text, 0, sizeof(char));
    state = hash_table;
    while(fread((void *)&c, 1, 1, file) != 0) {
        if(count < l_offset) {
            for(i=(sizeof(char)*8)-1; i>=0; i--) {
#               ifndef __TEST
                if(!state->left && !state->right) {
                    t_text = (char *)realloc((void *)t_text, strlen(t_text)+1);
                    strncat(t_text, &(state->c), 1);
                    state = hash_table;
                    i = i+1;
                    continue;
                }
                if(c&(1<<i)) {
                    state = state->right;
                }
                else {
                    state = state->left;
                }
#               else
                t_text = (char *)realloc((void *)t_text, strlen(t_text)+1);
                if(c&(1<<i)) {
                    x = '1';
                    strncat(t_text, &x, 1);
                    state = state->right;
                }
                else {
                    x = '0';
                    strncat(t_text, &x, 1);
                    state = state->left;
                }
#               endif
            }
            count++;
        }
        else {
            t_text = (char *)realloc((void *)t_text, strlen(t_text)+1);
            strncat(t_text, &c, 1);
        }
    }

#   ifdef __TEST
    fwrite((void *)t_text, sizeof(char), strlen(t_text), stdout);
#   endif

    return t_text;
}
