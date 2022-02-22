#include <stdio.h>
#include <stdlib.h>

typedef struct node 
{
    int number;
    struct node *next;
}
node;


int main(void)
{
    // List of size 0. We initialize the value to NULL explicitly, so there's
    // no garbage value for our list variable
    node *list = NULL;

    // Allocate memory for a node, n
    node *n = malloc(sizeof(node));
    if (n == NULL)
    {
        return 1;
    }

    // Set the value and pointer in our node
    n->number = 1;
    n->next = NULL;

    // Add node n by pointing list to it, since we only have one node so far
    list = n;

    // Allocate memory for another node, and we can reuse our variable n to
    // point to it, since list points to the first node already
    n = malloc(sizeof(node));
    if (n == NULL)
    {
        free(list);
        return 1;
    }

    // Set the values in our new node
    n->number = 2;
    n->next = NULL;

    // Update the pointer in our first node to point to the second node
    list->next = n;

    // Allocate memory for a third node
    n = malloc(sizeof(node));
    if (n == NULL)
    {
        // Free both of our other nodes
        free(list->next);
        free(list);
        return 1;
    }
    n->number = 3;
    n->next = NULL;

    // Follow the next pointer of the list to the second node, and update
    // the next pointer there to point to n
    list->next->next = n;

    // Print list using a loop, by using a temporary variable, tmp, to point
    // to list, the first node. Then, every time we go over the loop, we use
    // tmp = tmp->next to update our temporary pointer to the next node. We
    // keep going as long as tmp points to somewhere, stopping when we get to
    // the last node and tmp->next is null.
    for (node *tmp = list; tmp != NULL; tmp = tmp->next)
    {
        printf("%i\n", tmp->number);
    }

    // Free list, by using a while loop and a temporary variable to point
    // to the next node before freeing the current one
    while (list != NULL)
    {
        // We point to the next node first
        node *tmp = list->next;
        // Then, we can free the first node
        free(list);
        // Now we can set the list to point to the next node
        list = tmp;
        // If list is null, when there are no nodes left, our while loop will stop
    }
    
    return 0;
}
