#include "helpers.h"
#include <math.h>

BYTE LessThanByteSize (int n);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j ++)
        {
            BYTE average = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen  = average;
            image[i][j].rgbtBlue  = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j ++)
        {
            int sepiaRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            int sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            int sepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);
            image[i][j].rgbtRed = LessThanByteSize(sepiaRed);
            image[i][j].rgbtGreen = LessThanByteSize(sepiaGreen);
            image[i][j].rgbtBlue = LessThanByteSize(sepiaBlue);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        //j is first in line, k-1 is last in line, loop ends when middle of line, j increases, k decreases
        for (int j = 0, k = width - 1; j < round(width / 2.0); j ++, k--)
        {
            BYTE tmp;

            tmp = image[i][k].rgbtRed; //stores last value in line in tmp
            image[i][k].rgbtRed = image[i][j].rgbtRed; //swap first and last values
            image[i][j].rgbtRed = tmp; //stpres tmp in first value

            tmp = image[i][k].rgbtGreen; //same for green
            image[i][k].rgbtGreen = image[i][j].rgbtGreen;
            image[i][j].rgbtGreen = tmp;

            tmp = image[i][k].rgbtBlue; //same for blue
            image[i][k].rgbtBlue = image[i][j].rgbtBlue;
            image[i][j].rgbtBlue = tmp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    if (height < 2 || width < 2)
    {
        return;
    }

    //make a temporary copy of image
    RGBTRIPLE tmpimage[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j ++)
        {
            tmpimage[i][j].rgbtRed = image[i][j].rgbtRed;
            tmpimage[i][j].rgbtGreen = image[i][j].rgbtGreen;
            tmpimage[i][j].rgbtBlue = image[i][j].rgbtBlue;
        }
    }

    //loops to all lines and columns of image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j ++)
        {
            //add the pixel rgb values to the average
            int AvgRed = tmpimage[i][j].rgbtRed;
            int AvgGreen = tmpimage[i][j].rgbtGreen;
            int AvgBlue = tmpimage[i][j].rgbtBlue;
            int avgN = 1; //number of values added to average


            //for neighboring pixels checks if they're on image and adds their rgb value to their averega if yes
            if (i - 1 >= 0)
            {
                AvgRed = AvgRed + tmpimage[i - 1][j].rgbtRed;
                AvgGreen = AvgGreen + tmpimage[i - 1][j].rgbtGreen;
                AvgBlue = AvgBlue + tmpimage[i - 1][j].rgbtBlue;
                avgN ++;

                if (j - 1 >= 0)
                {
                    AvgRed = AvgRed + tmpimage[i - 1][j - 1].rgbtRed;
                    AvgGreen = AvgGreen + tmpimage[i - 1][j - 1].rgbtGreen;
                    AvgBlue = AvgBlue + tmpimage[i - 1][j - 1].rgbtBlue;
                    avgN ++;
                }

                if (j + 1 < width)
                {
                    AvgRed = AvgRed + tmpimage[i - 1][j + 1].rgbtRed;
                    AvgGreen = AvgGreen + tmpimage[i - 1][j + 1].rgbtGreen;
                    AvgBlue = AvgBlue + tmpimage[i - 1][j + 1].rgbtBlue;
                    avgN ++;
                }
            }

            if (i + 1 < height)
            {
                AvgRed = AvgRed + tmpimage[i + 1][j].rgbtRed;
                AvgGreen = AvgGreen + tmpimage[i + 1][j].rgbtGreen;
                AvgBlue = AvgBlue + tmpimage[i + 1][j].rgbtBlue;
                avgN ++;

                if (j - 1 >= 0)
                {
                    AvgRed = AvgRed + tmpimage[i + 1][j - 1].rgbtRed;
                    AvgGreen = AvgGreen + tmpimage[i + 1][j - 1].rgbtGreen;
                    AvgBlue = AvgBlue + tmpimage[i + 1][j - 1].rgbtBlue;
                    avgN ++;
                }

                if (j + 1 < width)
                {
                    AvgRed = AvgRed + tmpimage[i + 1][j + 1].rgbtRed;
                    AvgGreen = AvgGreen + tmpimage[i + 1][j + 1].rgbtGreen;
                    AvgBlue = AvgBlue + tmpimage[i + 1][j + 1].rgbtBlue;
                    avgN ++;
                }
            }

            if (j - 1 >= 0)
            {
                AvgRed = AvgRed + tmpimage[i][j - 1].rgbtRed;
                AvgGreen = AvgGreen + tmpimage[i][j - 1].rgbtGreen;
                AvgBlue = AvgBlue + tmpimage[i][j - 1].rgbtBlue;
                avgN ++;
            }

            if (j + 1 < width)
            {
                AvgRed = AvgRed + tmpimage[i][j + 1].rgbtRed;
                AvgGreen = AvgGreen + tmpimage[i][j + 1].rgbtGreen;
                AvgBlue = AvgBlue + tmpimage[i][j + 1].rgbtBlue;
                avgN ++;
            }

        image[i][j].rgbtRed = round(AvgRed / (float)avgN);
        image[i][j].rgbtGreen = round(AvgGreen / (float)avgN);
        image[i][j].rgbtBlue = round(AvgBlue / (float)avgN);

        }
    }
    return;
}

BYTE LessThanByteSize(int n)
{
    if (n <= 255)
    {
        return n;
    }
    else
    {
        return 255;
    }
}