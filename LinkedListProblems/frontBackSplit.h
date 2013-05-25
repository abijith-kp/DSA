//using 2 pointers fron both ends. since tail is not provided this method do
//not work
void frontBackSplit1(struct node **headRef) {
}


//using slow and fast pointer
void frontBackSplit(struct node **headRef, struct node **frontRef, struct node **backRef) {
        struct node *slow=*headRef, *fast=*headRef, *newHead=malloc(sizeof(struct node));

        if(!slow) {     //length = 0
                printf("\none\n");
                *frontRef = NULL;
                *backRef = NULL;
                return;
        }
        else if(!(slow->next)) {        //length = 1
                *frontRef = *headRef;
                printf("\ntwo\n");
                *backRef = NULL;
                return;
        }
        
        while((fast->next) && ((fast->next)->next)) {
                slow = slow->next;
                fast = (fast->next)->next;
        }
        
                printf("\nthree\n");
        *backRef = slow->next;
        slow->next = NULL;
        *frontRef = *headRef;
}
