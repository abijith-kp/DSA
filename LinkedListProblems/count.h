int count(struct node **headRef, int n) {
        int count=0;
        struct node *current = *headRef;

        while(current) {
                if(current->data == n)
                        count++;
                current = current->next;
        }

        return count;
}

int countSorted(struct node **headRef, int n) {
        int count=0;
        struct node *current = *headRef;

        while(current) {
                if(current->data > n)
                        break;
                else if(current->data == n)
                        count++;
                current = current->next;
        }
        return count;
}
