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

// User defined functions
bool add_word(node *dictionary[], node *word_node, size_t pos) {
    if (pos > N) { // This is kind of redudnant? Unlikely to happen?
        return false;
    }

    // if no element in "bucket"
    if (dictionary[pos] == NULL) {
        dictionary[pos] = word_node;
        dictionary[pos]->next = NULL;
        return true;
    }

    // If there were elements in "bucket" - Need to loop thorough them
    // Or should I just add them in the front?
    word_node->next = dictionary[pos]->next;
    dictionary[pos]->next = word_node;

    return true;
}

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

        // Converting to lowercase
        for (size_t i = 0; i < len; i++) {
            if (isalpha(word[i]))
                word[i] = tolower(word[i]);
        }

        // Creating node and initializing its word field with word
        node *n = malloc(sizeof(node));
        if (n == NULL) {
            printf("Error creating node for word %s.\n", word);
            printf("Loading of dictionary %s failed.\n", dictionary);
            return false;
        }
        strcpy(n->word, word);

        // Adding word to hash table
        printf("Initial of word %s is: %c and its number is: %d\n", n->word,
               n->word[0], n->word[0] - 'a');

        // Actually adding it

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
