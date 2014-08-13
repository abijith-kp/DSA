#include <stdio.h>
#include <stdlib.h>

struct node {
        int size;
        struct node *next;
}*tower[3];

void makeTower(int n) {
        struct node *tmp;
        int i;

        tower[0] = NULL;
        tower[1] = NULL;
        tower[2] = NULL;

        for(i=n; i>0; i--) {
                tmp = malloc(sizeof(struct node));
                tmp->size = i;
                tmp->next = tower[0];
                tower[0] = tmp;
        }
}

void show() {
        struct node *tmp[3] = {tower[0], tower[1], tower[2]};
        int a[3] = {0, 0, 0};
        int i = 1;
        
        while(tmp[0] ||  tmp[1] || tmp[2]) {
                i = 0;
                a[0] = 0;
                a[1] = 0;
                a[2] = 0;
                
                if(tmp[0]) {
                        a[0] = tmp[0]->size;
                        tmp[0] = tmp[0]->next;
                }
                if(tmp[1]) {
                        a[1] = tmp[1]->size;
                        tmp[1] = tmp[1]->next;
                }
                if(tmp[2]) {
                        a[2] = tmp[2]->size;
                        tmp[2] = tmp[2]->next;
                }
                printf("\n%d  %d  %d", a[0], a[1], a[2]);
        }
        
        if(i) {
                printf("\n%d  %d  %d\n", a[0], a[1], a[2]);
        }
        printf("\n-------------------------\n");
}

void push(int t, int n) {
        struct node *tmp = malloc(sizeof(struct node));
        tmp->size = n;
        tmp->next = tower[t];
        tower[t] = tmp;
}

int pop(int t) {
        int tmp;
        //struct node *twr = tower[t];
        tmp = tower[t]->size;
        tower[t] = tower[t]->next;

        return tmp;
}

void play(int start, int end, int n) {
        int tmp;
        
        show();
        if(n == 1) {
                tmp = pop(start);
                push(end, tmp);
                return;
        }
        
        play(start, (3-(start+end)), n-1);
        show();
        play(start, end, 1);
        show();
        play((3-(start+end)), end, n-1);
}

int main() {
        int n;

        printf("\nEnter the number of discs: ");
        scanf("%d", &n);

        if(n <= 0) {
                printf("Invalid input!!!!!\n");
                exit(1);
        }

        makeTower(n);
        //show();

        play(0, 2, n);
        show();
        
        return 0;
}
