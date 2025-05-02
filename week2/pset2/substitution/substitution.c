#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char *get_string(char *prompt);
void print_substituion(char* text, char* key);
int validate_key(char* key);

char *get_string(char *prompt) {
    printf("%s", prompt);
    char input[256];

    // Getting input
    while (fgets(input, sizeof input, stdin) == NULL) {
        printf("Error when reading input\n");
    }

    // First check and removing newline character
    size_t len = strlen(input);
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    }

    // Allocating memory to return
    char *result = malloc(strlen(input) + 1);
    if (result == NULL) {
        printf("Error allocating memory for string\n");
        return NULL;
    }

    // Copying string to be able to return a valid memory (and not something out
    // of scope)
    strcpy(result, input);

    return result;
}

int validate_key(char* key) {
    int v[26] = {0};
    size_t len_v = 26;
    size_t len_key = strlen(key);

    if (len_key != 26) {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    for (size_t i = 0; i < len_key; i++) {
        int index = toupper(key[i]) - 'A';
        for (size_t j = 0; j < len_v; j++) {
            if (v[index]) {
                printf("Can't have duplicate values in key\n");
                return 1;
            }
        }
        if (!isalpha(key[i])) {
            printf("Can't have non alphanumeric characters\n");
            return 1;
        }
        else {
            v[index] = 1;
        }
    }

    return 0;
}

void print_substituion(char* text, char* key) {
    size_t len_text = strlen(text);
    char result[256];
    for (size_t i = 0; i < len_text; i++) {
        if (!isalpha(text[i])) {
            result[i] = text[i];
        } else {
            if (isupper(text[i])) {
                result[i] = toupper(key[(((text[i] + 32) % 32) - 1)]);
            } else {
                result[i] = tolower(key[(((text[i] + 32) % 32) - 1)]);
            }
        }
    }
    result[len_text] = '\0';
    printf("ciphertext: %s\n", result);
}

int main(int argc, char* argv[]) {

    if (argc != 2) {
        printf("Usage: ./substition key\n");
        return 1;
    }

    char* key = argv[1];
    if (validate_key(key) == 1) {
        return 1;
    }

    char *ptext = get_string("plaintext: ");
    print_substituion(ptext, key);
    free(ptext);

    return 0;
}
