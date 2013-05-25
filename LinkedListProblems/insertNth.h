void insertNth(struct node **headRef, int pos, int data) {
        struct node *current = *headRef, *new = malloc(sizeof(struct node));
        new->data = data;

        if(pos <= 0) {
                new->next = *headRef;
                *headRef = new;
                return;
        }

        while(current) {
                if(pos == 1) {
                        new->next = current->next;
                        current->next = new;
                        return;
                }
                current = current->next;
                pos--;
        }
        if(pos > 0) {
                new->next = *headRef;
                *headRef = new;
        }
}
