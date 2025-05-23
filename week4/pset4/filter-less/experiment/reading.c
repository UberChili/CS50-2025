#include <stdio.h>
#include <stdlib.h>

#include "chunk.h"
#include "png.h"

/* const uint8_t png_signature[] = {0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A,
 * 0x0A}; */
const uint8_t png_signature[] = {137, 80, 78, 71, 13, 10, 26, 10};

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
    if (fread(&sh, sizeof(PNGSIGNATUREHEADER), 1, inptr) != 1) {
        printf("Error: Not enough bytes read for Signature Header\nNot a valid "
               "PNG file.\n");
        return 1;
    }

    for (size_t i = 0, n = sizeof(sh.values) / sizeof(uint8_t); i < n; i++) {
        printf("%02x ", sh.values[i]);
        /* printf("%u ", sh.values[i]); */
        if (sizeof sh.values != sizeof png_signature) {
            printf("Not a valid PNG file\n");
            return 1;
        } else if (sh.values[i] != png_signature[i]) {
            printf("Not a valid PNG file\n");
            return 1;
        }
    }
    printf("\nValid PNG file\n");

    // Read the first next chunk
    uint32_t length;
    if (fread(&length, sizeof(uint32_t), 1, inptr) != 1) {
        printf("Error: Couldn't read bytes for length\n");
        return 1;
    }
    CHUNK_TYPE chunk_type;
    if (fread(&chunk_type, sizeof(chunk_type.type_code), 1, inptr) != 1) {
        printf("Error: Couldn't read bytes for chunk type\n");
        return 1;
    }

    /* uint8_t data[length]; */
    uint8_t *data = malloc(sizeof(uint8_t) * length);
    if (fread(&data, sizeof(data), 1, inptr) == 0) {
        printf("Error: Couldn't read bytes for data\n");
        return 1;
    }
    /* uint8_t crc[4]; */
    uint8_t *crc = malloc(sizeof(uint8_t) * 4);
    if (fread(&crc, sizeof(crc), 1, inptr) == 0) {
        printf("Error: Couldn't read bytes for crc\n");
        return 1;
    }

    // do some sort of checking here
    printf("Chunk Type: %s\n", chunk_type.type_code);

    free(data);
    free(crc);
    fclose(inptr);
    return 0;
}
