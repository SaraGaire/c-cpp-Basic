#ifndef IO_H
#define IO_H

#include "tree.h"

tree_node *load_tree_from_file(const char *filename);
int save_tree_to_file(tree_node *root, const char *filename);

#endif
