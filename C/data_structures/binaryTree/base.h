struct node* newNode(int data) {
        struct node *new=malloc(sizeof(struct node));

        new->data = data;
        new->left = NULL;
        new->right = NULL;

        return new;
}

void insert(struct node **root, int data) {
        struct node *new=*root;
        
        if(!new) {
                *root = newNode(data);
                return;
        }
        
        while(new) {
                if(new->data >= data) {
                        if(new->left == NULL) {
                                new->left = newNode(data);
                                return;
                        }
                        new = new->left;
                }
                else {
                        if(new->right == NULL) {
                                new->right = newNode(data);
                                return;
                        }
                        new = new->right;
                }
        }
}

void show(struct node *root) {
        if(root == NULL)
                return;

        show(root->left);
        printf("\n%d\n", root->data);
        show(root->right);
}
