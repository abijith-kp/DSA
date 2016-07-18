#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#define MAX_SIZE 2048

struct HuffManNode
{
    int count;
    char data;
    char *code;
    struct HuffManNode *left, *right, *next;
};

typedef struct HuffManNode HMNode;

HMNode *listHead = NULL;
HMNode code_list[512];

FILE *out_fd = NULL;

int char_list[512];

HMNode *create_node(char data, int count)
{
    HMNode *tmp_node = calloc(1, sizeof(HMNode));
    tmp_node->data = data;
    tmp_node->count = count;
    tmp_node->code = NULL;
    tmp_node->left = NULL;
    tmp_node->right = NULL;
    tmp_node->next = NULL;
    return tmp_node;
}

void print_list()
{
    HMNode *tmp_node = listHead;
    printf("Display started\n");
    while (tmp_node)
    {
        printf("%c | %d\n", tmp_node->data, tmp_node->count);
        tmp_node = tmp_node->next;
    }
    printf("Display completed\n");
}

#define MEMBER(node) node->count

HMNode *combine_nodes(HMNode *node1, HMNode *node2)
{
    HMNode *tmp_node = calloc(1, sizeof(HMNode));
    tmp_node->next = NULL;
    tmp_node->count = node1->count + node2->count;
    tmp_node->data = 'X';

    if (MEMBER(node1) >= MEMBER(node2))
    {
        tmp_node->left = node1;
        tmp_node->right = node2;
    }
    else
    {
        tmp_node->left = node2;
        tmp_node->right = node1;
    }
    return tmp_node;
}


HMNode *insert_list(HMNode *list, HMNode *node)
{
    if (!list)
    {
        node->next = NULL;
        list = node;
        return list;
    }
    else
    {
        if (MEMBER(list) > MEMBER(node))
        {
            node->next = list;
            return node;
        }
        else
        {
            HMNode *tmp = list;
            int flag = 0;
            while (tmp->next)
            {
                if (MEMBER(tmp->next) < MEMBER(node))
                {
                    tmp = tmp->next;
                }
                else
                {
                    node->next = tmp->next->next;
                    tmp->next->next = node;
                    flag = 1;
                    break;
                }
            }
            if (!flag)
            {
                tmp->next = node;
                node->next = NULL;
            }
            return list;
        }
    }
}

HMNode *sort_list()
{
    HMNode *tmp_head = NULL;
    HMNode *tmp = NULL;

    while(listHead)
    {
        if (!tmp_head)
        {
            tmp_head = listHead;
            listHead = listHead->next;
            tmp_head->next = NULL;
        }
        else
        {
            tmp = tmp_head;
            if (MEMBER(tmp) > MEMBER(listHead))
            {
                HMNode *t = listHead;
                listHead = listHead->next;
                t->next = tmp;
                tmp_head = t;
            }
            else
            {
                int flag = 0;
                while (tmp->next)
                {
                    if (MEMBER(tmp->next) < MEMBER(listHead))
                        tmp = tmp->next;
                    else
                    {
                        HMNode *t = listHead;
                        listHead = listHead->next;
                        t->next = tmp->next;
                        tmp->next = t;
                        flag = 1;
                        break;
                    }
                }
                if (!flag)
                {
                    tmp->next = listHead;
                    listHead = listHead->next;
                    tmp->next->next = NULL;
                }
            }
        }
    }

    listHead = tmp_head;
    return listHead;
}

void insert_node(char c, int count)
{
    if (!listHead)
        listHead = create_node(c, count);
    else
    {
        HMNode *tmp = create_node(c, count);
        tmp->next = listHead;
        listHead = tmp;
    }
}

void reconstruct_list()
{
    int pos = 0;
    for (pos = -255; pos < 256; pos++)
    {
        int c = pos + 256;
        if (char_list[c])
            insert_node(pos, char_list[c]);
    }
}

void *process_buffer(void *arg_buffer)
{
    char *buffer = (char *)arg_buffer;
    for (; 0 != *buffer; buffer++)
        char_list[*buffer + 256] += 1;

    return NULL;
}

void print_inorder(HMNode *head)
{
    if (head)
    {
        if (head->left)
            print_inorder(head->left);
        if (head->right)
            print_inorder(head->right);
        else
            printf("(%c %s)\n", head->data, head->code);
    }
    else
    {
        printf("Tree is empty!!\n");
    }
}

HMNode *create_code(HMNode *tree)
{
    if (tree)
    {
        if (!(tree->code))
            tree->code = "";

        if (tree->left)
        {
            if (tree->left->code)
            {
                tree->left->code = realloc(tree->left->code, strlen(tree->left->code) + 1);
                strcpy(tree->left->code, "0");
            }
            else
            {
                tree->left->code = calloc(strlen(tree->code) + 2, sizeof(char));
                strcpy(tree->left->code, tree->code);
                strcat(tree->left->code, "0");
            }
            create_code(tree->left);
        }
        if (tree->right)
        {
            if (tree->right->code)
            {
                tree->left->code = realloc(tree->right->code, strlen(tree->right->code) + 1);
                strcpy(tree->right->code, "1");
            }
            else
            {
                tree->right->code = calloc(strlen(tree->code) + 2, sizeof(char));
                strcpy(tree->right->code, tree->code);
                strcat(tree->right->code, "1");
            }
            create_code(tree->right);
        }
    }

    return tree;
}

HMNode *create_tree()
{
    HMNode *node1, *node2, *tmp_node;

    if (listHead)
    {
        while (listHead->next)
        {
            node1 = listHead;
            node2 = listHead->next;
            listHead = listHead->next->next;
            node1->next = NULL;
            node2->next = NULL;
            tmp_node = combine_nodes(node1, node2);
            listHead = insert_list(listHead, tmp_node);
        }
    }

    return create_code(listHead);
}


HMNode *q_head = NULL, *q_tail = NULL;

void level_order_push(HMNode *node)
{
    if (!node)
        return;
    node->next = NULL;
    if (q_head)
        q_tail->next = node;
    else
        q_head = node;
    q_tail = node;
}

int find_len(HMNode *node)
{
    int len = 0;
    while(node)
    {
        len++;
        node = node->next;
    }

    return len;
}

void level_order_traversal(HMNode *head)
{
    if (head)
    {
        level_order_push(head);
        while (q_head)
        {
            printf("[%c %d] %d\n", q_head->data, q_head->count, find_len(q_head));
            level_order_push(q_head->left);
            level_order_push(q_head->right);
            if (q_head)
                q_head = q_head->next;
        }
    }
}

void print_encoding()
{
    int i = 0;
    int last_n = 0;
    char last_c = 0;

    for (i = 0; i < 512; i++)
    {
        if (code_list[i].count)
        {
            fprintf(out_fd, "(%c,%d)", code_list[i].data, code_list[i].count);
            last_n = code_list[i].count;
            last_c = code_list[i].data;
        }
    }
    fprintf(out_fd, "(%c,%d)", last_c, last_n);
}

void *encode(void *arg_buffer)
{
    char *buffer = (char *)arg_buffer;
    int i = 0;

    for (;; i += 1)
    {
        if ((buffer[i] == 0) || (i == MAX_SIZE))
            break;

        fprintf(out_fd, "%s", code_list[buffer[i] + 256].code);
    }
    
    return NULL;
}

void *decode(void *arg_buffer)
{
    char *buffer = (char *)arg_buffer;
    int i = 0;
    static HMNode *tmp_head = NULL;
    if (!tmp_head)
        tmp_head = listHead;
    for (;; i += 1)
    {
        // printf("\n%c", buffer[i]);
        if ((buffer[i] == 0) || (i == MAX_SIZE))
            break;

        if (buffer[i] == '0')
        {
            tmp_head = tmp_head->left;
        }
        else
        {
            tmp_head = tmp_head->right;
        }
        if (!(tmp_head->left) && !(tmp_head->right))
        {
            fprintf(out_fd, "%c", tmp_head->data);
            tmp_head = listHead;
        }
    }

    return NULL;
}

void process_fd(int fd, void *(funct_name)(void *arg))
{
    char buffer[MAX_SIZE];
    int exit_flag = 0, ret_val;
    
    for (;;)
    {
        memset(buffer, 0, MAX_SIZE);
        ret_val = read(fd, buffer, MAX_SIZE-1);
        if (ret_val < 0)
        {
            /* reading error */
            printf("Error while reading the file\n");
            return;
        }
        else if (ret_val < MAX_SIZE-1)
            exit_flag = 1;                          /* reading last max_size number of chars */

        funct_name(buffer);
        if (exit_flag)
            break;
    }
}


void process_file(char *filename, void *(funct_name)(void *arg))
{
    int fd = -1;
    
    fd = open(filename, O_RDONLY);
    if (fd <= 0)
    {
        printf("%s: file error. please check the file and try again!!\n", filename);
        return;
    }

    process_fd(fd, funct_name);
}

void create_code_list(HMNode *head)
{
    if (head)
    {
        if (head->left)
            create_code_list(head->left);
        if (head->right)
            create_code_list(head->right);
        else
        {
            code_list[head->data + 256].data = head->data;
            code_list[head->data + 256].code = head->code;
            code_list[head->data + 256].count = head->count;
        }
    }
    else
    {
        printf("Tree is empty!!\n");
    }
}

int load_encoding_data(char *filename)
{
    int last_n = 0, n;
    char last_c = 0, c;
    FILE *f = fopen(filename, "r");

    int fd;
    char buf[MAX_SIZE];

    for (;;)
    {
        fscanf(f, "(%c,%d)", &c, &n);

        if ((last_n == n) && (last_c == c))
            break;
        
        char_list[c + 256] = n;
        last_n = n;
        last_c = c;
    }

    fd = fileno(f);
    lseek(fd, ftell(f), SEEK_SET);
    
    return fd;
}

int main(int argc, char *argv[])
{
    int is_encode = -1;
    int decode_fd = 0;
    char *out_file = "output.file";

    if (argc != 5)
    {
        printf("\nUsage: %s [-e|-d] filename [-o output_file] \n", argv[0]);
        return -1;
    }

    if (!strncmp("-e", argv[1], 2))
        is_encode = 1;
    else if (!strncmp("-d", argv[1], 2))
        is_encode = 0;
    else
    {
        printf("\nUsage: %s [-e|-d] filename\n", argv[0]);
        return -1;
    }

    if (!strncmp("-o", argv[3], 2))
    {
        out_file = strdup(argv[4]);
    }

    if (is_encode)
        process_file(argv[2], process_buffer);
    else
        decode_fd = load_encoding_data(argv[2]); /* loads the encoding metadata and returns the fd of the open file */

    reconstruct_list();
    sort_list();
    listHead = create_tree();
    memset(code_list, 0, 512);
    create_code_list(listHead);
    out_fd = fopen(out_file, "w");

    if (is_encode)
    {
        print_encoding(); // to print metadata
        process_file(argv[2], encode);
    }
    else
    {
        process_fd(decode_fd, decode);
    }

    fclose(out_fd);

    return 0;
}
