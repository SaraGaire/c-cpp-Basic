#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

char *strdup_safe(const char *src) 
{
    char *dup = malloc(strlen(src) + 1);
    if (dup) strcpy(dup, src);
    return dup;
}

tree_node *create_leaf(const char *guess) 
{
    tree_node *node = malloc(sizeof(tree_node));
    node->text = strdup_safe(guess);
    node->yes = NULL;
    node->no = NULL;
    return node;
}

tree_node *create_node(const char *question, tree_node *yes_branch, tree_node *no_branch) 
{
    tree_node *node = malloc(sizeof(tree_node));
    node->text = strdup_safe(question);
    node->yes = yes_branch;
    node->no = no_branch;
    return node;
}

void free_tree(tree_node *root) 
{
    if (!root) return;
    free_tree(root->yes);
    free_tree(root->no);
    free(root->text);
    free(root);
}

void print_tree(tree_node *root, int depth) 
{
    if (!root) return;
    for (int i = 0; i < depth; ++i) printf("  ");
    printf("%s\n", root->text);
    print_tree(root->yes, depth + 1);
    print_tree(root->no, depth + 1);
}
