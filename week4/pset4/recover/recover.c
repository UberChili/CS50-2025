#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// A valid JPEG contains one of the following possibilities in its fourth byte
// starting from left to right
const uint8_t posibilities[] = {0xe0, 0xe1, 0xe2, 0xe3, 0xe4, 0xe5, 0xe6, 0xe7,
                                0xe8, 0xe9, 0xea, 0xeb, 0xec, 0xed, 0xee, 0xef};

int isValidJPEG(uint8_t contents[]) {
    if (contents[0] == 0xff && contents[1] == 0xd8 && contents[2] == 0xff) {
        for (size_t i = 0; i < sizeof(posibilities) / sizeof(uint8_t); i++) {
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

    uint8_t buffer[512];
    size_t bytes_read = 0;
    int counter = 0;
    while ((bytes_read = fread(buffer, sizeof(uint8_t), 512, fptr) != 0)) {
        if (feof(fptr)) {
            printf("Error reading contents from %s: EOF reached\n", argv[1]);
            break;
        }
        if (ferror(fptr)) {
            printf("Error reading contents from %s\n", argv[1]);
            break;
        }

        // We check for a header, if we find a header we can safely say we have
        // a JPEG image
        if (isValidJPEG(buffer)) {
            // Creating filename
            char filename[50] = ""; // This method is probably not best practice
            filename[0] = '\0';
            sprintf(filename, "%03d.jpg", counter);

            // Opening file to write
            FILE *outfptr = fopen(filename, "wb");
            if (outfptr == NULL) {
                printf("Error opening %s for writing\n", filename);
                return 1;
            }

            // Write that current chunk, likely the one containing the Header
            if (fwrite(buffer, sizeof(uint8_t), 512, outfptr) < 512) {
                printf("Error when writing Header chunk to file %s\n",
                       filename);
                return 1;
            }

            // Keep reading and writing until we form a full JPEG
            size_t chunk_bytes = 0;
            while ((chunk_bytes =
                        fread(buffer, sizeof(uint8_t), 512, fptr) != 0)) {
                if (feof(fptr)) {
                    printf("Error reading contents from %s: EOF reached\n",
                           argv[1]);
                    break;
                }
                if (ferror(fptr)) {
                    printf("Error reading contents from %s\n", argv[1]);
                    break;
                }
            }

            counter++;
        }
    }

    // Free memory and close files if not done yet
    fclose(fptr);
    return 0;
}
