// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

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
    dictionary[pos] = word_node;

    return true;
}

// Returns true if word is in dictionary, else false
bool check(const char *word) {
    // TODO
    const unsigned int w_hash = hash(word);

    if (table[w_hash] == NULL) {
        return false;
    }
    node *ptr = table[w_hash];
    while (ptr != NULL) {
        if (strcasecmp(ptr->word, word) == 0) {
            return true;
        } else {
            ptr = ptr->next;
        }
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word) {
    // TODO: Improve this hash function
    /* return toupper(word[0]) - 'A'; */
    // IDEA: Sum ASCII values, and take remainder of module number of buckets
    int sum = 0;
    for (int i = 0, w_len = strlen(word); i < w_len; i++) {
        sum += word[i];
    }
    return sum % N;
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

        // Converting to uppercase
        for (size_t i = 0; i < len; i++) {
            if (isalpha(word[i]))
                word[i] = toupper(word[i]);
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
        /* printf("Initial of word %s is: %c and its hashed number would be:
         * %d\n", */
        /*        n->word, n->word[0], n->word[0] - 'A'); */

        /* int calculated_hash = 0; */
        /* for (size_t i = 0, word_len = strlen(word); i < word_len; i++) { */
        /*     calculated_hash += word[i]; */
        /* } */
        /* /\* calculated_hash = calculated_hash / strlen(word) % N; *\/ */
        /* calculated_hash = calculated_hash % N; */
        /* printf("Initial of word %s is: %c and its hashed number would be:
         * %d\n", */
        /*        n->word, n->word[0], calculated_hash); */

        // Actually adding it
        if (!add_word(table, n, hash(word))) {
            return false;
        }

        free(n);
    }

    // close file and return
    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void) {
    // TODO
    /* return 0; */
    int count = 0;
    for (size_t i = 0; i < N; i++) {
        if (table[i] != NULL) {
            node *ptr = table[i];
            while (ptr != NULL) {
                count++;
                ptr = ptr->next;
            }
        } else {
            continue;
        }
    }
    return count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void) {
    // TODO
    for (size_t i = 0; i < N; i++) {
        if (table[i] != NULL) {
            node *ptr = table[i];
            node *aux = ptr;
            while (ptr->next != NULL) {
                aux = ptr;
                ptr = ptr->next;
                free(aux);
            }
        }
    }

    return true;
}
