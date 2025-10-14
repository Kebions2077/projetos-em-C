#include <stdio.h>
#include <stdlib.h>
typedef struct node
{
    int dado;
    struct node *next;
}
node;
int main (void)
{
    node *list = NULL;
    node *new = malloc(sizeof(node));

    new -> dado = 1;
    new -> next = NULL;
    new -> next = list;
    
    list = new;
    
     
    new = malloc(sizeof(node));
    
    
    new -> dado = 2;
    new -> next = NULL;
    new -> next = list;

    list = new;

    node *ultimo = list -> next;
    node *corrent = list;
    while(corrent != NULL)
    {
        printf("%i", corrent->dado);
        corrent = corrent -> next;
    }
}