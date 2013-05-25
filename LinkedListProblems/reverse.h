void reverse(struct node **headRef) {
        struct node *tmp, *new = *headRef, *newHead=malloc(sizeof(struct node));
        newHead = NULL;

        while(new) {
                push(&newHead, new->data);
                tmp = new->next;
                free(new);
                new = tmp;
        }
        *headRef = newHead;
}

void recursiveReverse(struct node **headRef) {
}
