#include "helpers.h"
#include <math.h>
#include <stdio.h>

BYTE AvgGxGy(int Gx, int Gy);

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

void blur(int height, int width, RGBTRIPLE image[height][width])
{
    if (height < 2 || width < 2)
    {
        return;
    }

    //make a temporary copy of image
    RGBTRIPLE tmpimage[height][width];
    for (int pH = 0; pH < height; pH++)
    {
        for (int pW = 0; pW < width; pW++)
        {
            tmpimage[pH][pW].rgbtRed = image[pH][pW].rgbtRed;
            tmpimage[pH][pW].rgbtGreen = image[pH][pW].rgbtGreen;
            tmpimage[pH][pW].rgbtBlue = image[pH][pW].rgbtBlue;
        }
    }

    //all pixels heights and widths
    for (int pH = 0; pH < height; pH++)
    {
        for (int pW = 0; pW < width; pW ++)
        {
            //initialize average variables
            int AvgRed = 0;
            int AvgGreen = 0;
            int AvgBlue = 0;
            int avgN = 0; //number of values added to average

            //neighbor pixels heights and widths
            for (int nH = pH - 1; nH <= pH + 1; nH++)
            {
                for (int nW = pW - 1; nW <= pW + 1; nW++)
                {
                    //neighbor pixels heights and widths are in image
                    if (nH >= 0 && nH < height && nW >= 0 && nW < width)
                    {
                        //add pixels colors values to respective averages
                        AvgRed += tmpimage[nH][nW].rgbtRed;
                        AvgGreen += tmpimage[nH][nW].rgbtGreen;
                        AvgBlue += tmpimage[nH][nW].rgbtBlue;
                        avgN += 1;
                    }
                }
            }
            //makes averages and stores to image
            image[pH][pW].rgbtRed = round(AvgRed / (float)avgN);
            image[pH][pW].rgbtGreen = round(AvgGreen / (float)avgN);
            image[pH][pW].rgbtBlue = round(AvgBlue / (float)avgN);
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    if (height < 2 || width < 2)
    {
        return;
    }

    //make a temporary copy of image
    RGBTRIPLE tmpimage[height][width];
    for (int pH = 0; pH < height; pH++)
    {
        for (int pW = 0; pW < width; pW++)
        {
            tmpimage[pH][pW].rgbtRed = image[pH][pW].rgbtRed;
            tmpimage[pH][pW].rgbtGreen = image[pH][pW].rgbtGreen;
            tmpimage[pH][pW].rgbtBlue = image[pH][pW].rgbtBlue;
        }
    }

    int GxKernel[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int GyKernel[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    //all pixels heights and widths
    for (int pH = 0; pH < height; pH++)
    {
        for (int pW = 0; pW < width; pW ++)
        {
            int GxRed = 0;
            int GxGreen = 0;
            int GxBlue = 0;

            int GyRed = 0;
            int GyGreen = 0;
            int GyBlue = 0;

            //neighbor pixels heights and widths
            for (int nH = pH - 1; nH <= pH + 1; nH++)
            {
                for (int nW = pW - 1; nW <= pW + 1; nW++)
                {

                    //neighbor pixels heights and widths are in image
                    if (nH >= 0 && nH < height && nW >= 0 && nW < width)
                    {
                        GxRed += tmpimage[nH][nW].rgbtRed * GxKernel[nH - pH + 1][nW - pW + 1];
                        GxGreen += tmpimage[nH][nW].rgbtGreen * GxKernel[nH - pH + 1][nW - pW + 1];
                        GxBlue += tmpimage[nH][nW].rgbtBlue * GxKernel[nH - pH + 1][nW - pW + 1];

                        GyRed += tmpimage[nH][nW].rgbtRed * GyKernel[nH - pH + 1][nW - pW + 1];
                        GyGreen += tmpimage[nH][nW].rgbtGreen * GyKernel[nH - pH + 1][nW - pW + 1];
                        GyBlue += tmpimage[nH][nW].rgbtBlue * GyKernel[nH - pH + 1][nW - pW + 1];
                    }
                }
            }
            image[pH][pW].rgbtRed = AvgGxGy(GxRed, GyRed);
            image[pH][pW].rgbtGreen = AvgGxGy(GxGreen, GyGreen);
            image[pH][pW].rgbtBlue = AvgGxGy(GxBlue, GyBlue);
        }
    }
    return;
}

BYTE AvgGxGy(int Gx, int Gy)
{
    Gx = round(sqrt((pow(Gx, 2) + pow(Gy, 2))));
    if (Gx <= 255)
    {
        return Gx;
    }
    else
    {
        return 255;
    }
}