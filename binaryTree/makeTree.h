struct stack *makeNode(struct node *tmp) {
        struct stack *sTmp=malloc(sizeo(struct stack));

        sTmp->point = &tmp;
        sTmp->next  = NULL;

        return sTmp;
}

void addQ(struct stack **tailR) {

}

void remQ(struct stack **headR) {

}

void add(struct node **root, int data) {
        struct stack *head, *tail;
        struct node *new=*root, *tmp;

        head = NULL;
        head = makeNode(new);
        tail = head;
        
        while(head) {
                tmp = head->left;
                if(tmp)
                        addQ(&tail, tmp);
                else {
                        head->left = newNode(data);
                        return;
                }
                
                tmp = head->right;
                if(tmp)
                        addQ(&tail, tmp);
                else {
                        head->right = newNode(data);
                        return;
                }
                remQ(&head);
        }
}

struct node *makeTree() {
        int i, n, tmp;
        struct node *root=malloc(sizeof(struct node));
        root = NULL;

        printf("\nenter the no. of input: ");
        scanf("%d", &n);
        for(i=0; i<n; i++) {
                printf("\nenter the data in the node %d: ", i+i);
                scanf("%d", &tmp);
                add(&root, tmp);
        }
        return root;
}
