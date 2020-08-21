// Implements a dictionary's functionality

#include <stdbool.h>

#include "dictionary.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

int wordCount = 0;

// Number of buckets in hash table
const unsigned int N = 26*26*26;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    int index = hash(word);
    //node *cursor = malloc(sizeof(node));
    node *cursor = table[index];
    
    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
        else
        {
            cursor = cursor->next;
        }
    }
    // TODO
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned int temp[strlen(word)];
    int lower[strlen(word)];
    
    for (int i = 0; i < strlen(word); i++)
    {
        lower[i] = tolower(word[i]);
    }
    
    for (int i = 0; i < strlen(word); i++)
        {
            temp[i] = lower[i] - 97;
        }
    
    if ((strlen(word) < 3 || temp[1] < 0 || temp[2] < 0) && (temp[0] >= 0))
    {
        return temp[0];
    }
    else if (strlen(word) >= 3 && temp[0] >= 0)
    {
        return temp[0]*26*26 + temp[1]*26 + temp[2];
    }
    
    return 0;
    // TODO
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    char entry[LENGTH + 1];

    FILE *dic = fopen(dictionary, "r");
    if (!dic)
    {
        return 1;
    }

    while (fscanf(dic, "%s", entry) != EOF)
    {
        int temp[LENGTH + 1];
        int index;
        for (int i = 0; i < strlen(entry); i++)
        {
            temp[i] = entry[i] - 97;
        }

        if (strlen(entry) < 3 || temp[0] < 0 || temp[1] < 0 || temp[2] < 0)
        {
            index = temp[0];
        }
        else
        {
            index = temp[0]*26*26 + temp[1]*26 + temp[2];
        }

        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            printf("No mems left buddy");
            return false;
        }
        strcpy(n->word, entry);
        n->next = NULL;

        if (table[index] == NULL)
        {
            table[index] = n;
        }
        else
        {
            n->next = table[index];
            table[index] = n;
        }
        wordCount++;
        //free(n);

    }
    if (fscanf(dic, "%s", entry) == EOF)
        {
            fclose(dic);
            return true;
        }

    // TODO
    return false;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return wordCount;
    // TODO

}

// Unloads dictionary from memory, returning true if successful else false

bool unload(void)
{
    
    //node *cursor = malloc(sizeof(node));
    //node *temp = malloc(sizeof(node));
    
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        while (cursor)
        {
            node *temp = cursor->next;
            free(cursor);
            cursor = temp;
        }
    }
    
    return true;
    // TODO
    
}
