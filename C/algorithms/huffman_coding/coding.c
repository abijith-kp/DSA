#include <stdio.h>
#include <unistd.h>
#include <ctype.h>

#include "hash_table.h"
#include "huffman.h"
#include "content.h"

#define VERSION "0.0"
#define READ_SIZE 1024
#define HEADER 1024
#define EXT ".henc"

char *i_file=NULL, *o_file=NULL, *file_text=NULL;
int fin_flag=0, fout_flag=0;
int code_opt = -1;
ht *hash_table = NULL;

void decode() {
    char *content;
    FILE *d_file, *open_file;

    open_file = fopen(i_file, "rb");
    if(!open_file){
        fprintf(stderr, "File cannot be opened.\n");
        exit(1);
    }
    if(fout_flag == 1)
        d_file = fopen(o_file, "w");
    else
        d_file = stdout;

    content = get_content(open_file);
    if(!content) {
        fprintf(stderr, "Error in decompressing the input file.\n"
                        "Aborting decompression.\n");
        exit(2);
    }

    fprintf(d_file, "%s", content);

    if(d_file != stdout)
        fclose(d_file);
}

void encode() {
    size_t len = 0;
    ht *node1, *node2, *t;
    ht *char_map=NULL;
    FILE *e_file, *open_file;
    int fd, read_bytes;
    char buffer[READ_SIZE+1];

    open_file = fopen(i_file, "r");
    if(!open_file){
        fprintf(stderr, "File cannot be opened.\n");
        exit(1);
    }
    fd = fileno(open_file);

    while((read_bytes=read(fd, buffer, READ_SIZE)) != 0) {
        buffer[read_bytes] = '\0';
        if(!file_text)
            file_text = strdup(buffer);
        else {
            file_text = (char *)realloc(file_text, read_bytes+strlen(file_text));
            strcat(file_text, buffer);
        }
    }
    fclose(open_file);
    hash_table = make_table(hash_table, file_text);

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

#   if (defined __TEST) && (defined __TABLE)
    show_tree(hash_table);
    printf("\n\n");
#   endif

    if(fout_flag == 1)
        e_file = fopen(o_file, "wb");
    else
        e_file = stdout;

    put_content(file_text, char_map, e_file);

    if(e_file != stdout)
        fclose(e_file);
}

static void usage() {
    printf("Huffman encoding and decoding\n\n"
           "\tUsage:                       \n"
           "\t   -f  -  input given as file   \n"
           "\t   -o  -  output file   \n"
           "\t   -e  -  flag for encoding(default option)   \n"
           "\t   -d  -  flag for decoding   \n"
           "\t   -h  -  print this help and exit\n"
           "Version: %s\n", VERSION);
}

int main(int argc, char **argv) {
    char c;

    while ((c = getopt (argc, argv, "hedo:f:")) != -1) {
        switch (c)
        {
            case 'f':
                fin_flag = 1;
                i_file = optarg;
                break;
            case 'o':
                fout_flag = 1;
                o_file = optarg;
                break;
            case 'e':
                if(code_opt != -1) {
                    fprintf(stderr, "either encoding or decoding flag should "
                                    "be provided\n");
                    exit(2);
                }
                code_opt = 0;
                break;
            case 'd':
                if(code_opt != -1) {
                    fprintf(stderr, "either encoding or decoding flag should "
                                    "be provided\n");
                    exit(2);
                }
                code_opt = 1;
                break;
            case 'h':
                usage();
                exit(0);
            case '?':
                if ((optopt == 'f') || (optopt == 'o'))
                    fprintf (stderr, "Option -%c requires an argument.\n",
                            optopt);
                else if (isprint (optopt))
                    fprintf (stderr, "Unknown option `-%c'.\n", optopt);
                else
                    fprintf (stderr,
                            "Unknown option character `\\x%x'.\n",
                            optopt);
            default:
                exit(1);
        }
    }

    if(fin_flag != 1) {
        fprintf(stderr, "Input file not provided.\n");
        exit(1);
    }

    if(code_opt == 0)
        encode();
    else
        decode();

    return 0;
}
