// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define CHANNEL_NUM_OFFSIZE 22
#define BITS_PER_SAMPLE_OFFSIZE 34

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

    float factor = atof(argv[3]);

    // TODO: Copy header from input file to output file
    char *buff = malloc(HEADER_SIZE);
    if (fread(buff, HEADER_SIZE, 1, input) == 0) {
        printf("Couldn't read header\n");
    }

    /* for (size_t i = 0, n = HEADER_SIZE; i < n; i++) { */
    /*     printf("%zu\t%02X\n", i + 1, (unsigned char) buff[i]); */
    /* } */
    /* uint16_t num_channels = *(uint16_t*) (buff + CHANNEL_NUM_OFFSIZE); */
    /* uint16_t bits_per_sample = *(uint16_t*) (buff + BITS_PER_SAMPLE_OFFSIZE); */

    if (fwrite(buff, HEADER_SIZE, 1, output) < 1) {
        printf("Couldn't write header\n");
    }
    free(buff);


    // TODO: Read samples from input file and write updated data to output file
    uint16_t sample;
    while (fread(&sample, sizeof(uint16_t), 1, input)) {
        sample *= factor;
        fwrite(&sample, sizeof(uint16_t), 1, output);
    }

    // Close files
    fclose(input);
    fclose(output);
}
