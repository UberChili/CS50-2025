#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char* get_string(char* prompt);

char* get_string(char* prompt) {
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
    char* result = malloc(strlen(input) + 1);
    if (result == NULL) {
        printf("Error allocating memory for string\n");
        return NULL;
    }

    // Copying string to be able to return a valid memory (and not something out of scope)
    strcpy(result, input);

    return result;
}

int main(void) {


    return 0;
}
