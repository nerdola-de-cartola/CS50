// Implements a dictionary's functionality
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <strings.h>
#include <stdbool.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 10000;

// Hash table
node *table[N];

//This global variable keeps track of the number of words loaded from the dictionary
unsigned int WORDSCOUNT = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    //Loops for each node in the linked list
    for (node *tmp = table[hash(word)]; tmp != NULL; tmp = tmp->next)
    {
        //Is the word in the node the same as the word passed in the parameters?
        if ((strcasecmp(tmp->word, word)) == 0)
        {
            return true;
        }
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned long hash = 5381;
    int c;

    while ((c = toupper(*word++)))
    {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }

    return (hash % N);
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *dictionary_file = fopen(dictionary, "r");

    if (dictionary_file == NULL)
    {
        return false;
    }

    //Keeps the current word readed from the dictionary
    char dictionary_word[LENGTH + 1];

    //Loop untill the dictionary is over
    while (fscanf(dictionary_file, "%s", dictionary_word) != EOF)
    {
        //n is the pointer used to insert new nodes
        node *n = malloc(sizeof(node));

        if (n == NULL)
        {
            return false;
        }

        //Complete the n node
        strcpy(n->word, dictionary_word);
        n->next = NULL;

        //This variables stores the result of the hash function
        unsigned int index = hash(dictionary_word);

        //If the list have at least one node
        if (table[index] != NULL)
        {

            //tmp is the temporary node that the program uses to remeber the linked list
            node *tmp = table[index];

            //If the list have more than one node
            if (tmp->next != NULL)
            {
                n->next = tmp->next;
            }

            tmp->next = n;
        }
        //If the list have no nodes yet
        else
        {
            table[index] = n;
        }

        WORDSCOUNT++;
    }

    fclose(dictionary_file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return WORDSCOUNT;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    //Loops for each index in the table array
    for (int i = 0; i < N; i++)
    {
        //Loops for each node in the linked list
        for (node *cursor = table[i], *tmp = cursor; cursor != NULL; tmp = cursor)
        {
            if (tmp == NULL)
            {
                return false;
            }

            //Move cursor foward
            cursor = cursor->next;

            free(tmp);
        }
    }
    return true;
}
