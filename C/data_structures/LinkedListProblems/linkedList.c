#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct node {
        int data;
        struct node *next;
};

int ERROR = -1;
//ERROR = 1 ==> getNth error
//      = 2 ==> pop error

#include "basic.h"
#include "count.h"
#include "getNth.h"
#include "deleteList.h"
#include "insertNth.h"
#include "sortedInsert.h"
#include "insertSort.h"
#include "append.h"
#include "frontBackSplit.h"
#include "removeDuplicates.h"
#include "reverse.h"

int main() {
        int t;
        struct node *head = NULL, *new, *newHead;
        new = malloc(sizeof(struct node));
        new->data = 334;
        
        newHead = malloc(sizeof(struct node));
        newHead = NULL;
        
        push(&head, 0);
        push(&head, 1);
        push(&head, 2);
        push(&head, 1);
        show(head);
        
        printf("No. of occurences of 4 is %d\n", count(&head, 1));
        
        t = getNth(&head, 1);
        if(ERROR == 1)
                printf("ERROR: invalid value for index\n");
        else
                printf("%dth value in the list is %d\n", 1, t);

        printf("\n---------------------------------\n");
        show(head);
        deleteList(&head);
        printf("\n---------------------------------\n");
        show(head);


        sortedInsert(&head, new);
        push(&head, 1);
        push(&head, 1);
        push(&head, 1);
        push(&head, 1);
        push(&head, 1);
        printf("\n---------------------------------\n");
        show(head);
        insertSort(&head);
        printf("\n---------------------------------\n");
        show(head);

        push(&newHead, 10);
        push(&newHead, 11);
        push(&newHead, 12);
        push(&newHead, 11);
        printf("\n2---------------------------------\n");
        show(newHead);

        append(&head, &newHead);
        printf("\n3---------------------------------\n");
        show(head);
        printf("\n2sdfdsfsd---------------------------------\n");
        show(newHead);

        frontBackSplit(&head, &head, &newHead);
        printf("\n4---------------------------------\n");
        show(head);
        printf("\n5---------------------------------\n");
        show(newHead);

        removeDuplicates(&head);
        printf("\n6 new---------------------------------\n");
        show(head);
        
        reverse(&newHead);
        printf("\n7 zxkjcdsnew---------------------------------\n");
        show(newHead);
        return 0;
}
