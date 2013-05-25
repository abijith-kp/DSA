void sortedInsert(struct node **headRef, struct node *newNode) {
        struct node *new = *headRef;
        newNode->next = NULL;

        if(!new) {
                *headRef = newNode;
                return;
        }

        if(new->data >= newNode->data) {
                newNode->next = new;
                *headRef = newNode;
                return;
        }

        while(new->next) {
                if((new->next)->data >= newNode->data) {
                        newNode->next = new->next;
                        new->next = newNode;
                        break;
                }
                new = new->next;
        }
        
        new->next = newNode;
}
