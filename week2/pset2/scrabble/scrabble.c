#include <stdio.h>
#include <string.h>
#include <stdlib.h>


char* get_string(char* prompt);
int score(char* text);

const int points[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int main(void) {

    char *player1 = get_string("Player 1: ");
    char *player2 = get_string("Player 2: ");

    int score_player1 = score(player1);
    int score_player2 = score(player2);

    if (score_player1 == score_player2) {
        printf("Tie!\n");
    } else if (score_player1 > score_player2) {
        printf("Player 1 wins!\n");
    } else {
        printf("Player 2 wins!\n");
    }

    // Freeing memory and returning
    free(player1);
    free(player2);
    return 0;
}

int score(char* text) {
    int len = strlen(text);
    if (len == 0 ) {
        return 0;
    }

    int sum = 0;
    for (int i = 0; i < len; i++) {
        sum += points[i];
    }
    return sum;
}

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
