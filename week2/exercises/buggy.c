#include <stdio.h>
#include <stdlib.h>


void print_column(int height);
int get_int(char* prompt);

int main(void) {

    int h = get_int("Height: ");
    if (h == 0) {
        return 1;
    }

    print_column(h);

    return 0;
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


void print_column(int height) {
    for (int i = 0; i < height; i++) {
        printf("#\n");
    }
}
