#include "hash_table.h"

//TODO: optimize the algorithm
ht *make_table(ht *head_ref, char *text) {
    int f=0;
    ht *head = head_ref, *t;

    while(*text != '\0') {
        head = head_ref;
        if(!head) {
            head_ref = LEAF_NODE(*text, 1, "");
            text++;
            continue;
        }
        else if(head->c == *text) {
            head->count += 1;
            text++;
            continue;
        }

        f = 0;
        while(head->next) {
            if((head->next)->c == *text) {
                (head->next)->count += 1;
                f = 1;
                break;
            }
            head = head->next;
        }
        if(f != 1)
            head->next = LEAF_NODE(*text, 1, "");
        text++;
    }

    head = head_ref;
    head_ref = NULL;
    while(head) {
        t = head->next;
        head->next = NULL;
        head_ref = add_node(&head_ref, head);
        head = t;
    }

    return head_ref;
}

/**
 * min-priority queue implementation
 **/

void show_tree(ht *head_ref) {
    if(head_ref->left)
        show_tree(head_ref->left);
    if(!head_ref->left && !head_ref->right)
        printf("\n[%c] %d [%s]\n", head_ref->c, head_ref->count, head_ref->code);
    if(head_ref->right)
        show_tree(head_ref->right);
}

ht *get_min(ht **head_ref) {
    ht *head = *head_ref, *t;
    int min = -1;

    while(head) {
        if(min == -1) {
            min = head->count;
        }
        else if(min > head->count) {
            min = head->count;
        }
        head = head->next;
    }

    head = *head_ref;
    if(head->count == min) {
        *head_ref = head->next;
        head->next = NULL;
        return head;
    }
    while(head->next) {
        if((head->next)->count == min) {
            t = head->next;
            head->next = (head->next)->next;
            t->next = NULL;
            return t;
        }
        head = head->next;
    }

    return NULL;
}

ht *add_node(ht **head_ref, ht *node) {
    ht *head = *head_ref;
    if(!head) {
        node->next = NULL;
        return node;
    }
    else {
        if(head->c > node->c) {
            node->next = head;
            *head_ref = node;
            return *head_ref;
        }
    }
    while(head->next) {
        if((head->next)->c > (node->c)) {
            node->next = head->next;
            head->next = node;
            return *head_ref;
        }
        head = head->next;
    }

    head->next = node;
    return *head_ref;
}

size_t len_ht(ht *head_ref){
    size_t l=0;
    while(head_ref){
        l += 1;
        head_ref = head_ref->next;
    }

    return l;
}
