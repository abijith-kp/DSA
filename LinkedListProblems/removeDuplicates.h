void removeDuplicates(struct node **headRef) {
        struct node *new=*headRef, *tmp;
        
        while(new) {
                if(countSorted(&new, new->data) > 1) {
                        *headRef = new->next;
                        free(new);
                }
                else
                        break;
                
                new = *headRef;
        }

        //tmp = new;
        while(new->next) {
                if(count(&(new->next), (new->next)->data) > 1) {
                        new->next = (new->next)->next;
                }
                else {
                        new = new->next;
                }
        }
}
