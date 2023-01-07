// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <math.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

//size of dictionary, counted in load funcion
unsigned int s = 0;

//hash table
const unsigned int Letters = 26; //letters in alphabet
const unsigned int N_letters = 4; //number of letters to hash
const unsigned int N_hash = 456976; // (int)pow(Letters,N_letters)
node *table[N_hash]; // hash table

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    node *current_node = table[hash(word)];
    while (current_node != NULL)
    {
        if (strcasecmp(current_node->word, word) == 0)
        {
            return true;
        }
        current_node = current_node->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int h = 0;
    int i = 0;
    while (i < N_letters && word[i] != '\0')
    {
        h += (toupper(word[i]) - 'A') * pow(Letters, N_letters - 1 - i);
        i++;
    }
    return h;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open dictionary file
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }

    //for each word in dictionary until the end of file
    char word[LENGTH + 1];
    node *new_node;
    while (fscanf(file, "%s", word) != EOF)
    {
        // allocate a new node for word
        new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            return false;
        }

        //hash word and copy to node
        unsigned int h = hash(word);
        strcpy(new_node->word, word);

        // Insert node to beguining of linked list at hast table
        new_node->next = table[h]; //node points to adress of first node linked list
        table[h] = new_node; //node becomes the beguinning of has table
        s++;
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return s;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    node *current_node;
    for (int i = 0; i < N_hash; i++)
    {
        while (table[i] != NULL)
        {
            current_node = table[i];
            table[i] = current_node->next;
            free(current_node);
        }
    }
    return true;
}
