struct node *deleteList(struct node **headRef) {
        if(!(*headRef))
                return NULL;

        if(!((*headRef)->next)) {
                free(*headRef);
                return NULL;
        }

        printf("\ndelete\n");
        deleteList(&((*headRef)->next));
        free(*headRef);
        *headRef = NULL;

        return *headRef;
}
