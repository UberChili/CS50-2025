#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// A valid JPEG contains one of the following possibilities in its fourth byte
// starting from left to right
const uint8_t posibilities[] = {0xe0, 0xe1, 0xe2, 0xe3, 0xe4, 0xe5, 0xe6, 0xe7,
                                0xe8, 0xe9, 0xea, 0xeb, 0xec, 0xed, 0xee, 0xef};

int isValidJPEG(uint8_t contents[]) {
    if (contents[0] == 0xff && contents[1] == 0xd8 && contents[2] == 0xff) {
        for (size_t i = 0, n = sizeof(posibilities) / sizeof(uint8_t); i < n;
             i++) {
            if (contents[3] == posibilities[i]) {
                return 1;
            }
        }
    }
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: ./recover file\n");
        return 1;
    }

    FILE *fptr = fopen(argv[1], "rb");
    if (fptr == NULL) {
        printf("Error opening file %s\n", argv[1]);
        return 1;
    }
}
