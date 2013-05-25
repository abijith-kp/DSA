#include <stdio.h>
#include <stdlib.h>

struct node {
        int data;
        struct node *right, *left;
};

struct stack {
                struct node **point;
                struct stack *next;
};

#include "base.h"
#include "size.h"
#include "maxDepth.h"
#include "makeTree.h"

int main() {
        struct node *root;

        root = makeTree();
        show(root);

        return 0;
}
