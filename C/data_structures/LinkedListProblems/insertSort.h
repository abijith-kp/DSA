//not in-place sort. new head node is created

void insertSort(struct node **headRef) {
        struct node *new = *headRef, *newHead=malloc(sizeof(struct node)), *tmp;
        newHead = NULL;

        while(new) {
                tmp = new->next;
                new->next = NULL;
                sortedInsert(&newHead, new);
                new = tmp;
        }

        //free(*headRef);
        *headRef = newHead;
}
