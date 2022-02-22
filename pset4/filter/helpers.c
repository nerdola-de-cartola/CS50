#include <math.h>
#include <stdlib.h>

#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int red;
    int green;
    int blue;
    int averageColor;

    //loops through each pixel for each pixel
    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width; column++)
        {
            //Gets the amount of each color in the current pixel
            red = image[row][column].rgbtRed;
            green = image[row][column].rgbtGreen;
            blue = image[row][column].rgbtBlue;

            //Calculate the average color of the pixel
            averageColor = round((float)(red + green + blue) / 3);

            //Set all colors to the average(gray) color
            image[row][column].rgbtRed = averageColor;
            image[row][column].rgbtGreen = averageColor;
            image[row][column].rgbtBlue = averageColor;
        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE originalPixel;

    int red;
    int green;
    int blue;

    //loops through each pixel for each pixel
    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width; column++)
        {
            //Copy the current pixel into a temporary variable
            originalPixel = image[row][column];

            //Uses the Sepia Algorithms to calculate the amount of each color
            red = round((float) 0.393 * originalPixel.rgbtRed + 0.769 * originalPixel.rgbtGreen + 0.189 * originalPixel.rgbtBlue);
            green = round((float) 0.349 * originalPixel.rgbtRed + 0.686 * originalPixel.rgbtGreen + 0.168 * originalPixel.rgbtBlue);
            blue = round((float) 0.272 * originalPixel.rgbtRed + 0.534 * originalPixel.rgbtGreen + 0.131 * originalPixel.rgbtBlue);

            //Puts the new colors in the real image as long as the value is not greater than 255
            image[row][column].rgbtRed = red > 255 ? 255 : red;
            image[row][column].rgbtGreen = green > 255 ? 255 : green;
            image[row][column].rgbtBlue = blue > 255 ? 255 : blue;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmpImage[height][width];
    int count;

    //loops through each pixel
    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width; column++)
        {
            //Puts the all the opposite pixel into a temporary image
            tmpImage[row][column] = image[row][width - (column + 1)];
        }
    }

    //loops through each pixel
    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width; column++)
        {
            //Copy the temporary image into the real image
            image[row][column] = tmpImage[row][column];
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmpImage[height][width];

    int neighborColumn;
    int neighborRow;
    int neighborCount;

    int sumRed;
    int sumGreen;
    int sumBlue;

    //Loop for each pixel
    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width; column++)
        {
            //Reset variables
            sumRed = 0;
            sumGreen = 0;
            sumBlue = 0;
            neighborCount = 0;

            //Loop for each neighbor
            for (int i = -1; i < 2; i++)
            {
                //Verify if the neighbor is a valid pixel
                neighborRow = row + i;

                if (neighborRow >= 0 && neighborRow < height)
                {

                    for (int j = -1; j < 2; j++)
                    {
                        neighborColumn = column + j;

                        if (neighborColumn >= 0 && neighborColumn < width)
                        {

                            //Add current pixel colors to total
                            sumRed += image[neighborRow][neighborColumn].rgbtRed;
                            sumGreen += image[neighborRow][neighborColumn].rgbtGreen;
                            sumBlue += image[neighborRow][neighborColumn].rgbtBlue;

                            //Calculate who many neighbors the current pixel have
                            neighborCount++;
                        }
                    }
                }
            }

            //Puts blur pixels in a temporary image
            tmpImage[row][column].rgbtRed = round((float) sumRed / neighborCount);
            tmpImage[row][column].rgbtGreen = round((float) sumGreen / neighborCount);
            tmpImage[row][column].rgbtBlue = round((float) sumBlue / neighborCount);
        }
    }

    //Copy all pixels back to the original image
    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width; column++)
        {
            image[row][column] = tmpImage[row][column];
        }
    }
}