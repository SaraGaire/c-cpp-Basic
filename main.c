
#include <stdlib.h>
#include "tree.h"
#include "game.h"
#include "io.h"

#define SAVE_FILE "knowledge.txt"

int main(void) 
{
    int c;
    puts("Guess What Game");

    tree_node *root = load_tree_from_file(SAVE_FILE);

    if (!root)
    {
        printf("starting with default knowledge...\n");
        root = create_leaf("a bicycle");
    }

    while (1) 
    {
        play_game(&root);
        printf("hit <enter> key to continue ...\n");
        while((c = getchar()) != '\n');
        if (!get_yes_no("play again? (y/n) ")) break;
    }

    if (save_tree_to_file(root, SAVE_FILE)) 
        printf("knowledge saved to '%s'\n", SAVE_FILE);
    else 
        printf("failed to save knowledge\n");

    free_tree(root);

    puts("thanks for playing");
    return EXIT_SUCCESS;
}
