#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "io.h"

#define BUFFER 512

// helper function for  recursively writing  the tree to file
static void save_node(tree_node *node, FILE *fp) 
{
    if (!node) return;
    if (!node->yes && !node->no)
        fprintf(fp, "A:%s\n", node->text);  // A for answer (leaf)
    else {
        fprintf(fp, "Q:%s\n", node->text);  // Q for question for undersatanfing it
        save_node(node->yes, fp);
        save_node(node->no, fp);
    }
}

int save_tree_to_file(tree_node *root, const char *filename) 
{
    FILE *fp = fopen(filename, "w");
    if (!fp) return 0;
    save_node(root, fp);
    fclose(fp);
    return 1;
}//saving and loading the files

// helper: recursively read the tree from file
static tree_node *load_node(FILE *fp) 
{
    char buffer[BUFFER];
    if (!fgets(buffer, BUFFER, fp)) return NULL;

    buffer[strcspn(buffer, "\n")] = '\0'; // removes newline

    if (strncmp(buffer, "A:", 2) == 0) {
        return create_leaf(buffer + 2);
    } else if (strncmp(buffer, "Q:", 2) == 0) {
        tree_node *yesBranch = load_node(fp);
        tree_node *noBranch = load_node(fp);
        return create_node(buffer + 2, yesBranch, noBranch);
    }
    return NULL;
}

tree_node *load_tree_from_file(const char *filename) 
{
    FILE *fp = fopen(filename, "r");
    if (!fp) return NULL;
    tree_node *root = load_node(fp);
    fclose(fp);
    return root;
}
