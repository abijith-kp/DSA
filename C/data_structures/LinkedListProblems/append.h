void append(struct node **aRef, struct node **bRef) {
        struct node *aTmp=*aRef;

        if(!aTmp) {
                *aRef = *bRef;
                *bRef = NULL;
                return;
        }

        while(aTmp->next)
                aTmp = aTmp->next;

        aTmp->next = *bRef;
        *bRef = NULL;
}
