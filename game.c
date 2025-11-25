#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"
#include "game.h"
//all the header files.

#define BUFFER 256
//it helps in optimization of the memmory storage.

char *read_line(const char *msg) 
{
    static char buffer[BUFFER];
    //thsi buffer presist between the function calladn retail its value.
    printf("%s", msg);
    if (fgets(buffer, BUFFER, stdin)) 
    {
        buffer[strcspn(buffer, "\n")] = 0;
        return buffer;
    }
    return NULL;
    //checks if the fget return null valye or not.
}

int get_yes_no(const char *msg) 
//declaring a function retrun yes and no
{
    while (1) //thsi will create a infinite loop.
    {
        char *input = read_line(msg);//function call
        if (!input) return 0;//when its null or any EOF which will then treat no or exit.
        if (strcmp(input, "y") == 0 || strcmp(input, "Y") == 0) return 1;
        if (strcmp(input, "n") == 0 || strcmp(input, "N") == 0) return 0;
        printf("please answer with 'y' or 'n'\n");//if anyother option is entered then the display will shwo the error.
        //check for the yes and no if true then y and if n then false.
    }
}

void ask(tree_node **node) 
{
    static char command[BUFFER];
    if (!(*node)) return;

    if (!(*node)->yes && !(*node)->no) 
    {
        // leaf node - make a guess
        printf("is it %s? (y/n): ", (*node)->text);
        
        if (get_yes_no(command)) 
            puts("i congratulate myself!");
        else 
        {
            // learn new thing
            char *correct = strdup(read_line("i give up. What are you thinking about? "));  
            char *question = strdup(read_line("enter a question to distinguish your answer: "));
            int answer_yes = get_yes_no("what is the answer for your object? (y/n) ");

            tree_node *new_guess = create_leaf(correct);
            tree_node *old_guess = *node;

            *node = create_node(question,
                answer_yes ? new_guess : old_guess,
                answer_yes ? old_guess : new_guess);

            //system("cowsay -t \"i've learned something new\" | lolcat");
            puts("i've learned something new today");
        }
    } 
    else 
    {
        // internal question node
        printf("%s (y/n) ",(*node)->text);
        int answer = get_yes_no(command);
        if (answer) 
            ask(&(*node)->yes); 
        else 
            ask(&(*node)->no);
    }
}

void play_game(tree_node **root) 
{
    int c;
    printf("think of something... hit <enter> key when ready ...\n");
    while((c = getchar()) != '\n');
    ask(root);
}
