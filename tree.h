#ifndef TREE_H
#define TREE_H

typedef struct tree_node 
{
    char *text;
    struct tree_node *yes;
    struct tree_node *no;
} tree_node;

// tree operations
tree_node *create_leaf(const char *guess);
tree_node *create_node(const char *question, tree_node *yes_branch, tree_node *no_branch);
void free_tree(tree_node *root);
void print_tree(tree_node *root, int depth);

#endif
