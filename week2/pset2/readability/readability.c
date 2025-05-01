#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *get_string(char *prompt);

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

int calc_coleman_liau(char *text) {
    int letters = 0;
    int words = 0;
    int sentences = 0;

    size_t len = strlen(text);

    if (len > 0) {
        words++;
    }

    for (int i = 0; i < len; i++) {
        if (text[i] == '.' || text[i] == '?' || text[i] == '!') {
            sentences++;
        } else if (isspace(text[i])) {
            words++;
        } else if (isalpha(text[i])) {
            letters++;
        }
    }

    // calculate letters and sentences averages
    float L = ((float)letters / words) * 100.0;
    float S = ((float)sentences / words) * 100.0;

    // return index
    return 0.0588 * L - 0.296 * S - 15.8;
}

int main(void) {

    char *text = get_string("Text: ");

    int index = calc_coleman_liau(text);
    free(text);

    if (index < 1) {
        printf("Before Grade 1\n");
    } else if (index > 15) {
        printf("Grade %d+\n", index);
    } else {
        printf("Grade %d\n", index);
    }

    return 0;
}
