#include <stdio.h>
#include <stdlib.h>


int get_int(char* prompt);
float average(int array[], int length);


int main(void) {
    int scores[3];
    const int scores_len = sizeof(scores) / sizeof(int);

    for (int i = 0; i < scores_len; i++) {
        scores[i] = get_int("score: ");
    }

    // Calculate average
    float avg = average(scores, scores_len);
    printf("Average: %f\n", avg);

    return 0;
}


float average(int array[], int length) {
    int adding = 0;
    for (int i = 0; i < length; i++) {
        adding += array[i];
    }
    return adding / (float) length;
}

int get_int(char* prompt) {
    printf("%s", prompt);
    char input[256];
    fgets(input, sizeof input, stdin);

    int height = atoi(input);
    if (height == 0) {
        printf("Error: input needs to be a number\n");
        return 0;
    }

    return height;
}
