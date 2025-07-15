// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node {
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word) {
    // TODO
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word) {
    // TODO: Improve this hash function
    return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary) {
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL) {
        printf("Error loading dictionary %s\n", dictionary);
        return false;
    }

    // Read all words - they're separated by lines
    char word[256];
    while (fgets(word, sizeof(word), dict) != NULL) {
        // Removing newline character
        size_t len = strlen(word);
        if (len > 0 && word[len - 1] == '\n') {
            word[len - 1] = '\0';
        }

        // Creating node and inserting word
        node *n = malloc(sizeof(node));
        if (n == NULL) {
            printf("Error creating node for word %s.\n", word);
            printf("Loading of dictionary %s failed.\n", dictionary);
            return false;
        }
        strcpy(n->word, word);

        // Adding word to hash table

        free(n);
    }

    // close file and return
    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void) {
    // TODO
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void) {
    // TODO
    return false;
}
