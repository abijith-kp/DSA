void push(struct node **headRef, int data) {
        struct node *current, *new = (struct node *)malloc(sizeof(struct node));
        current = *headRef;
        new->data = data;
        new->next = NULL;

        if(current == NULL)
                *headRef = new;
        else {
                new->next = *headRef;
                *headRef = new;
        }

        return;
}

int pop(struct node **headRef) {
        int t;

        if(!(*headRef)) {
                ERROR = 2;
                return 0;
        }
        struct node *new = *headRef;
        t = new->data;

        *headRef = (*headRef)->next;
        free(new);
        return t;
}

void show(struct node *head) {
        while(head) {
                printf("\n>> %d\n", head->data);
                head = head->next;
        }
}
