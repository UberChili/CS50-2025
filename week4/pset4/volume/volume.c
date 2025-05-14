// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
/* const int HEADER_SIZE = 44; */
const size_t HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    /* float factor = atof(argv[3]); */

    // TODO: Copy header from input file to output file
    // first let's try to understand how to "read" the header
    // (HEADER_SIZE is an int of value 44)
    char *buff = malloc(HEADER_SIZE);
    if (fread(buff, HEADER_SIZE, 1, input) == 0) {
        printf("Couldnt read header\n");
    }

    for (size_t i = 0, n = HEADER_SIZE; i < n; i++) {
        printf("%zu\t%02X\n", i + 1, (unsigned char) buff[i]);
    }

    free(buff);

    // TODO: Read samples from input file and write updated data to output file

    // Close files
    fclose(input);
    fclose(output);
}
