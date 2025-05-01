#include <ctype.h>
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

int calc_coleman_liau(char* text) {
    int letters = 0;
    int words = 0;

    for (int i = 0; i < strlen(text); i++) {
        if (!isalpha(text[i])) {
            letters++;
        } else if (text[i] == ' ') {
            words++;
        }
    }

    // calculate letters and sentences averages
    float L = letters / 100.0;
    float S = words / 100.0;

    // return index
    return (0.0588 * L) - (0.296 * S) - 15.8;
}

int main(void) {

    char* text = get_string("Text: ");

    int index = calc_coleman_liau(text);
    printf("%d\n", index);

    return 0;
}
