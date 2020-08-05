#include "helpers.h"
#include <math.h>

// Convert image to grayscale - got help from Neel
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    //declares the integer average
    int average;
    //creates nested forloop that moves through the 2x2 array of pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //variable of datatype RGBTRIPLE is set to be equal to whichever pixel we are examining in the array
            RGBTRIPLE bob = image[i][j];
            //computes the average of all of the color components of each pixel
            average = round((float)((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0));
            //sets each of the image pixel color components to the average of the three
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    //sets up a nested forloop that goes through each pixel of 2x2 pixel array
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //computes the sepia color components of each pixel
            int sepiaRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            int sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            int sepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);

            //ensures that the sepia components are capped at 255
            if (sepiaRed >= 255)
            {
                sepiaRed = 255;
            }

            if (sepiaGreen >= 255)
            {
                sepiaGreen = 255;
            }

            if (sepiaBlue >= 255)
            {
                sepiaBlue = 255;
            }
            //applies sepia filter to the image
            image[i][j].rgbtBlue = sepiaBlue;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtRed = sepiaRed;
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    //creates a nested forloop that goes through each pixel of the 2x2 array of pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            //creates a temporary variable to store the color information of the original pixel
            RGBTRIPLE temp = image[i][j];
            //swaps the original image pixel's color information with that of the opposite on the horizontal row
            //since we are only reflecting horizontally, i does not change of the opposite pixel, but j does
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;
        }
    }
    return;
}

// Blur image
// helped by walkthrough with reese on October 5
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //declares an array of pixels copied from the OG image with elements of type RGBTRIPLE
    RGBTRIPLE imageCopy[height][width];

    //nested forloop that moves through OG image array of pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //initializes and declares the R, G, and B sums and number of pixels to 0
            int sumR = 0;
            int sumG = 0;
            int sumB = 0;
            int numPixels = 0;
            //a nested forloop that iterates through the pixels surrounding a pixel and gets a total sum and number of pixels
            //to be computed into the average
            for (int row = i - 1; row <= i + 1; row++)
            {
                for (int col = j - 1; col <= j + 1; col++)
                {
                    //if statement makes sure that edge pixels are accounted for as they have less actual surrounding pixels
                    if (0 <= col && 0 <= row && col < width && row < height)
                    {
                        sumR += image[row][col].rgbtRed;
                        sumG += image[row][col].rgbtGreen;
                        sumB += image[row][col].rgbtBlue;
                        numPixels++;
                    }
                }
            }
            //computes total average of surrounding pixels for R, G, and B
            int averageR = round(sumR / (numPixels * 1.0));
            int averageG = round(sumG / (numPixels * 1.0));
            int averageB = round(sumB / (numPixels * 1.0));

            //puts the new computed pixel color components into a copy image, so that they OG image's color components are
            //used to calculate the new averages for all pixels
            imageCopy[i][j].rgbtGreen = averageG;
            imageCopy[i][j].rgbtBlue = averageB;
            imageCopy[i][j].rgbtRed = averageR;
        }
    }
    //nested forloop that copies pixel by pixel each element of the copy image to the OG image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = imageCopy[i][j];
        }
    }
    return;
}
