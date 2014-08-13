int size(struct node *root) {
        if(!root)
                return 0;
        
        return(size(root->left) + 1 + size(root->right));
}
