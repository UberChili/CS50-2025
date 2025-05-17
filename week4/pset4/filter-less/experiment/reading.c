#include <stdio.h>

#include "png.h"

/* const uint8_t png_signature[] = {0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A}; */
const uint8_t png_signature[] = {137, 80, 78, 71, 13, 10, 26, 10 };

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: ./reading <png file>\n");
    }


    // Open input file
    char *infile = argv[1];
    FILE *inptr = fopen(infile, "rb");
    if (inptr == NULL) {
        printf("Could not open %s\n", infile);
        return 1;
    }

    // Read infile's PNGSIGNATUREHEADER and determine if
    // it is a valid PNG file
    PNGSIGNATUREHEADER sh;
    fread(&sh, sizeof(PNGSIGNATUREHEADER), 1, inptr);

    for (size_t i = 0, n = sizeof(sh.values) / sizeof(uint8_t); i < n; i++) {
        /* printf("%02x ", sh.values[i]); */
        if (sizeof sh.values != sizeof png_signature) {
            printf("Not a valid PNG file\n");
            return 1;
        }
        else if (sh.values[i] != png_signature[i]) {
            printf("Not a valid PNG file\n");
            return 1;
        }
    }
    printf("Valid PNG file\n");

    // Read the first next chunk

    fclose(inptr);
    return 0;
}
