int getNth(struct node **headRef, int n) {
        struct node *current = *headRef;

        while(current) {
                if(n < 0)
                        break;

                if(n == 0)
                        return current->data;
                
                current = current->next;
                n--;
        }

        if((n >= 0) || (n < 0)) {
                ERROR = 1;
                return 0;
        }

        return 0;
}

