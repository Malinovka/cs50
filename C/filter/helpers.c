#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int y = 0 ; y < height; y++) {
        for (int x = 0; x < width; x++) {

            //Load current pixel into buffer
            RGBTRIPLE buffer = image[y][x];

            //Average out and update rgb values
            image[y][x].rgbtBlue = round( (double) (buffer.rgbtBlue + buffer.rgbtGreen + buffer.rgbtRed) / 3);
            image[y][x].rgbtGreen = round( (double) (buffer.rgbtBlue + buffer.rgbtGreen + buffer.rgbtRed) / 3);
            image[y][x].rgbtRed = round( (double) (buffer.rgbtBlue + buffer.rgbtGreen + buffer.rgbtRed) / 3);
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < round( (double) width / 2); x++) {

            //Load current pixel into buffer
            RGBTRIPLE buffer = image[y][x];

            //Swap opposite pixels on the x axis
            image[y][x] = image[y][width - x - 1];
            image[y][width - x - 1] = buffer;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy_image[height][width];
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            copy_image[y][x] = image[y][x];
        }
    }

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {

            int avgblue = 0;
            int avggreen = 0;
            int avgred =0;
            int counter = 0;

            for (int grid_y = -1; grid_y <= 1; grid_y++) {
                //Continue to next loop is the grid is out of bounds
                if (y + grid_y < 0 || y + grid_y >= height) {
                    continue;
                }

                for (int grid_x = -1; grid_x <= 1; grid_x++) {
                    //Continue to next loop if the grid is out of bounds
                    if (x + grid_x < 0 || x + grid_x >= width) {
                        continue;
                    }

                    //Add up the color values in a 3 by 3 grid surrounding the current pixel
                    avgblue += copy_image[y + grid_y][x + grid_x].rgbtBlue;
                    avggreen += copy_image[y + grid_y][x + grid_x].rgbtGreen;
                    avgred += copy_image[y + grid_y][x + grid_x].rgbtRed;
                    counter++;
                }
            }

            //Change pixel color to the averaged values
            image[y][x].rgbtBlue = round( (double) avgblue / counter);
            image[y][x].rgbtGreen = round( (double) avggreen / counter);
            image[y][x].rgbtRed = round( (double) avgred / counter);
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy_image[height][width];
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            copy_image[y][x] = image[y][x];
        }
    }

    //sobel array
    int sobel[] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {

            int gx_blue = 0;
            int gx_green = 0;
            int gx_red = 0;
            int gy_blue = 0;
            int gy_green = 0;
            int gy_red = 0;

            //calculate gx values
            for (int grid_y = -1, counter = 0; grid_y <= 1; grid_y++) {
                for (int grid_x = -1; grid_x <= 1; grid_x++) {
                    //Continue to next loop if the grid is out of bounds
                    if (x + grid_x < 0 || x + grid_x >= width || y + grid_y < 0 || y + grid_y >= height) {
                        counter++;
                        continue;
                    }

                    //Add up the color values in a 3 by 3 grid surrounding the current pixel
                    gx_blue += copy_image[y + grid_y][x + grid_x].rgbtBlue * sobel[counter];
                    gx_green += copy_image[y + grid_y][x + grid_x].rgbtGreen * sobel[counter];
                    gx_red += copy_image[y + grid_y][x + grid_x].rgbtRed * sobel[counter];
                    counter++;
                }
            }

            //calculate gy
            for (int grid_x = -1, counter = 0; grid_x <= 1; grid_x++) {
                for (int grid_y = -1; grid_y <= 1; grid_y++) {
                    //Continue to next loop if the grid is out of bounds
                    if (x + grid_x < 0 || x + grid_x >= width || y + grid_y < 0 || y + grid_y >= height) {
                        counter++;
                        continue;
                    }

                    //Add up the color values in a 3 by 3 grid surrounding the current pixel
                    gy_blue += copy_image[y + grid_y][x + grid_x].rgbtBlue * sobel[counter];
                    gy_green += copy_image[y + grid_y][x + grid_x].rgbtGreen * sobel[counter];
                    gy_red += copy_image[y + grid_y][x + grid_x].rgbtRed * sobel[counter];
                    counter++;
                }
            }

            //Calculate final color value
            int blue = round(sqrt( (double) (gx_blue * gx_blue) + (gy_blue * gy_blue)));
            if (blue < 0) {
                blue = 0;
            }
            if (blue > 255) {
                blue = 255;
            }

            int green = round(sqrt( (double) (gx_green * gx_green) + (gy_green * gy_green)));
            if (green < 0) {
                green = 0;
            }
            if (green > 255) {
                green = 255;
            }
            int red = round(sqrt( (double) (gx_red * gx_red) + (gy_red * gy_red)));
            if (red < 0) {
                red = 0;
            }
            if (red > 255) {
                red = 255;
            }

            //Change pixel color to the new values
            image[y][x].rgbtBlue = blue;
            image[y][x].rgbtGreen = green;
            image[y][x].rgbtRed = red;
        }
    }
    return;
}
