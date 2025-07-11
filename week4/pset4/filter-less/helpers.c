#include "helpers.h"
#include <math.h>

int calcAverageRGB(RGBTRIPLE rgb) {
    return round((rgb.rgbtRed + rgb.rgbtGreen + rgb.rgbtBlue) / 3.0);
}

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width]) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int average = calcAverageRGB(image[i][j]);
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width]) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int sepiaRed = round((0.393 * image[i][j].rgbtRed) +
                                 (0.769 * image[i][j].rgbtGreen) +
                                 (0.189 * image[i][j].rgbtBlue));
            if (sepiaRed > 255) {
                sepiaRed = 255;
            }
            int sepiaGreen = round((0.349 * image[i][j].rgbtRed) +
                                   (0.686 * image[i][j].rgbtGreen) +
                                   (0.168 * image[i][j].rgbtBlue));
            if (sepiaGreen > 255) {
                sepiaGreen = 255;
            }
            int sepiaBlue = round((0.272 * image[i][j].rgbtRed) +
                                  (0.534 * image[i][j].rgbtGreen) +
                                  (0.131 * image[i][j].rgbtBlue));
            if (sepiaBlue > 255) {
                sepiaBlue = 255;
            }

            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width]) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width / 2; j++) {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = temp;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width]) {
    RGBTRIPLE temp[height][width];

    for (int currentRow = 0; currentRow < height; currentRow++) {
        for (int currentCol = 0; currentCol < width; currentCol++) {

            int sumRed = 0;
            int sumGreen = 0;
            int sumBlue = 0;
            int pixelCount = 0;

            for (int rowOffset = -1; rowOffset <= 1; rowOffset++) {
                for (int colOffset = -1; colOffset <= 1; colOffset++) {
                    int neighborRow = currentRow + rowOffset;
                    int neighborCol = currentCol + colOffset;

                    if (neighborRow >= 0 && neighborRow < height &&
                        neighborCol >= 0 && neighborCol < width) {

                        sumRed += image[neighborRow][neighborCol].rgbtRed;
                        sumGreen += image[neighborRow][neighborCol].rgbtGreen;
                        sumBlue += image[neighborRow][neighborCol].rgbtBlue;
                        pixelCount++;
                    }
                }
            }

            temp[currentRow][currentCol].rgbtRed =
                round((float)sumRed / pixelCount);
            temp[currentRow][currentCol].rgbtGreen =
                round((float)sumGreen / pixelCount);
            temp[currentRow][currentCol].rgbtBlue =
                round((float)sumBlue / pixelCount);
        }
    }

    // Copy blurred image back to original
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            image[i][j] = temp[i][j];
        }
    }
}
