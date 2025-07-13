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
    // Check for correct usage and store filename
    if (argc != 2) {
        printf("Usage: ./recover file\n");
        return 1;
    }
    const char *input = argv[1];

    // Open file to search in
    FILE *fptr = fopen(argv[1], "rb");
    if (fptr == NULL) {
        printf("Error opening file %s\n", input);
        return 1;
    }

    // The variables we'll use to keep track of things
    int counter = 0;
    uint8_t buffer[512];
    FILE *curr_out = NULL;
    size_t bytes_read = 0;
    // Main "reading" loop
    while ((bytes_read = fread(buffer, sizeof(uint8_t), 512, fptr)) == 512) {
        if (ferror(fptr)) {
            printf("Error when reading from file %s\n", input);
            break;
        }

        // Check if found a valid JPEG Signature Header
        if (isValidJPEG(buffer)) {
            // Close current file if open
            if (curr_out != NULL) {
                fclose(curr_out);
            }

            // Create new filename and open new file
            char filename[50];
            sprintf(filename, "%03d.jpg", counter);

            curr_out = fopen(filename, "wb");
            if (curr_out == NULL) {
                printf("Error opening file %s\n", filename);
                break;
            }

            // Write current buffer to file
            fwrite(buffer, sizeof(uint8_t), bytes_read, curr_out);

            counter++;
        } else if (curr_out != NULL) {
            // We're in the middle of a JPEG - keep writing
            fwrite(buffer, sizeof(uint8_t), bytes_read, curr_out);
        }
    }

    // Close files and free memory if needed
    fclose(fptr);
    // don't forget to close last file if it's still open
    if (curr_out != NULL) {
        fclose(curr_out);
    }
    return 0;
}
