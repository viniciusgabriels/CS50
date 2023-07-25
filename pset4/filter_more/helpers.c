#include "helpers.h"
#include <math.h>
#include <stdio.h>

void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    BYTE avg;
    float favg;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            avg = (BYTE)((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            favg = ((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);

            if ((favg - avg) >= 0.5)
            {
                avg++;
            }

            image[i][j].rgbtRed = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtBlue = avg;
        }
    }
    return;
}

void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    BYTE sepiaRed;
    BYTE sepiaGreen;
    BYTE sepiaBlue;
    float fsepiaRed;
    float fsepiaGreen;
    float fsepiaBlue;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {

            sepiaRed = (int)(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            fsepiaRed = (.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);

            if ((fsepiaRed - sepiaRed) >= 0.5)
            {
                sepiaRed++;
            }

            if (fsepiaRed >= 255)
            {
                sepiaRed = 255;
            }

            sepiaGreen = (int)(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            fsepiaGreen = (.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);

            if ((fsepiaGreen - sepiaGreen) >= 0.5)
            {
                sepiaGreen++;
            }

            if (fsepiaGreen >= 255)
            {
                sepiaGreen = 255;
            }

            sepiaBlue = (int)(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);
            fsepiaBlue = (.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);

            if ((fsepiaBlue - sepiaBlue) >= 0.5)
            {
                sepiaBlue++;
            }

            if (fsepiaBlue >= 255)
            {
                sepiaBlue = 255;
            }

            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < (width / 2); j++)
        {
            temp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;
        }
    }
    return;
}

void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height + 2][width + 2];

    int ci = 0;
    int cl = height + 1;
    for (int q = 0; q < height + 2; q++)
    {
        for (int w = 0; w < width + 2; w++)
        {
            if (q == 0)
            {
                copy[q][w].rgbtRed = 0;
                copy[q][w].rgbtGreen = 0;
                copy[q][w].rgbtBlue = 0;
            }

            if (q == height + 1)
            {
                copy[q][w].rgbtRed = 0;
                copy[q][w].rgbtGreen = 0;
                copy[q][w].rgbtBlue = 0;
            }
        }
        copy[q][ci].rgbtRed = 0;
        copy[q][ci].rgbtGreen = 0;
        copy[q][ci].rgbtBlue = 0;
        copy[q][cl].rgbtRed = 0;
        copy[q][cl].rgbtGreen = 0;
        copy[q][cl].rgbtBlue = 0;
    }

    for (int k = 1; k < height + 1; k++)
    {
        for (int l = 1; l < width + 1; l++)
        {
            copy[k][l] = image[k - 1][l - 1];
        }
    }

    int integar[3];
    float floats[3];
    int cornersi[3];
    float cornersf[3];
    int rowsi[3];
    float rowsf[3];

    for (int i = 1; i < height + 1; i++)
    {
        for (int j = 1; j < width + 1; j++)
        {
            if ((i == 1 && j == 1) || (i == 1 && j == width) || (i == height && j == 1) || (i == height && j == width))
            {
                cornersi[0] = ((copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed + copy[i][j - 1].rgbtRed + copy[i - 1][j - 1].rgbtRed +
                                copy[i - 1][j].rgbtRed + copy[i - 1][j + 1].rgbtRed + copy[i + 1][j - 1].rgbtRed + copy[i + 1][j].rgbtRed +
                                copy[i + 1][j + 1].rgbtRed) /
                               4);
                cornersi[1] = ((copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen + copy[i][j - 1].rgbtGreen + copy[i - 1][j - 1].rgbtGreen +
                                copy[i - 1][j].rgbtGreen + copy[i - 1][j + 1].rgbtGreen + copy[i + 1][j - 1].rgbtGreen + copy[i + 1][j].rgbtGreen +
                                copy[i + 1][j + 1].rgbtGreen) /
                               4);
                cornersi[2] = ((copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i - 1][j - 1].rgbtBlue +
                                copy[i - 1][j].rgbtBlue + copy[i - 1][j + 1].rgbtBlue + copy[i + 1][j - 1].rgbtBlue + copy[i + 1][j].rgbtBlue +
                                copy[i + 1][j + 1].rgbtBlue) /
                               4);

                cornersf[0] = ((copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed + copy[i][j - 1].rgbtRed + copy[i - 1][j - 1].rgbtRed +
                                copy[i - 1][j].rgbtRed + copy[i - 1][j + 1].rgbtRed + copy[i + 1][j - 1].rgbtRed + copy[i + 1][j].rgbtRed +
                                copy[i + 1][j + 1].rgbtRed) /
                               4.0);
                cornersf[1] = ((copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen + copy[i][j - 1].rgbtGreen + copy[i - 1][j - 1].rgbtGreen +
                                copy[i - 1][j].rgbtGreen + copy[i - 1][j + 1].rgbtGreen + copy[i + 1][j - 1].rgbtGreen + copy[i + 1][j].rgbtGreen +
                                copy[i + 1][j + 1].rgbtGreen) /
                               4.0);
                cornersf[2] = ((copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i - 1][j - 1].rgbtBlue +
                                copy[i - 1][j].rgbtBlue + copy[i - 1][j + 1].rgbtBlue + copy[i + 1][j - 1].rgbtBlue + copy[i + 1][j].rgbtBlue +
                                copy[i + 1][j + 1].rgbtBlue) /
                               4.0);

                for (int h = 0; h < 3; h++)
                {
                    if (cornersf[h] - cornersi[h] >= 0.5)
                    {
                        cornersi[h]++;
                    }
                    if (cornersi[h] > 255)
                    {
                        cornersi[h] = 255;
                    }
                }
                image[i - 1][j - 1].rgbtRed = cornersi[0];
                image[i - 1][j - 1].rgbtGreen = cornersi[1];
                image[i - 1][j - 1].rgbtBlue = cornersi[2];
            }

            else if ((i == 1) || (i == height) || (j == 1) || (j == width))
            {
                rowsi[0] = ((copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed + copy[i][j - 1].rgbtRed + copy[i - 1][j - 1].rgbtRed +
                             copy[i - 1][j].rgbtRed + copy[i - 1][j + 1].rgbtRed + copy[i + 1][j - 1].rgbtRed + copy[i + 1][j].rgbtRed +
                             copy[i + 1][j + 1].rgbtRed) /
                            6);
                rowsi[1] = ((copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen + copy[i][j - 1].rgbtGreen + copy[i - 1][j - 1].rgbtGreen +
                             copy[i - 1][j].rgbtGreen + copy[i - 1][j + 1].rgbtGreen + copy[i + 1][j - 1].rgbtGreen + copy[i + 1][j].rgbtGreen +
                             copy[i + 1][j + 1].rgbtGreen) /
                            6);
                rowsi[2] = ((copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i - 1][j - 1].rgbtBlue +
                             copy[i - 1][j].rgbtBlue + copy[i - 1][j + 1].rgbtBlue + copy[i + 1][j - 1].rgbtBlue + copy[i + 1][j].rgbtBlue +
                             copy[i + 1][j + 1].rgbtBlue) /
                            6);

                rowsf[0] = ((copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed + copy[i][j - 1].rgbtRed + copy[i - 1][j - 1].rgbtRed +
                             copy[i - 1][j].rgbtRed + copy[i - 1][j + 1].rgbtRed + copy[i + 1][j - 1].rgbtRed + copy[i + 1][j].rgbtRed +
                             copy[i + 1][j + 1].rgbtRed) /
                            6.0);
                rowsf[1] = ((copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen + copy[i][j - 1].rgbtGreen + copy[i - 1][j - 1].rgbtGreen +
                             copy[i - 1][j].rgbtGreen + copy[i - 1][j + 1].rgbtGreen + copy[i + 1][j - 1].rgbtGreen + copy[i + 1][j].rgbtGreen +
                             copy[i + 1][j + 1].rgbtGreen) /
                            6.0);
                rowsf[2] = ((copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i - 1][j - 1].rgbtBlue +
                             copy[i - 1][j].rgbtBlue + copy[i - 1][j + 1].rgbtBlue + copy[i + 1][j - 1].rgbtBlue + copy[i + 1][j].rgbtBlue +
                             copy[i + 1][j + 1].rgbtBlue) /
                            6.0);

                for (int h = 0; h < 3; h++)
                {
                    if (rowsf[h] - rowsi[h] >= 0.5)
                    {
                        rowsi[h]++;
                    }
                    if (rowsi[h] > 255)
                    {
                        rowsi[h] = 255;
                    }
                }

                image[i - 1][j - 1].rgbtRed = rowsi[0];
                image[i - 1][j - 1].rgbtGreen = rowsi[1];
                image[i - 1][j - 1].rgbtBlue = rowsi[2];
            }
            else
            {
                integar[0] = ((copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed + copy[i][j - 1].rgbtRed + copy[i - 1][j - 1].rgbtRed +
                               copy[i - 1][j].rgbtRed + copy[i - 1][j + 1].rgbtRed + copy[i + 1][j - 1].rgbtRed + copy[i + 1][j].rgbtRed +
                               copy[i + 1][j + 1].rgbtRed) /
                              9);
                integar[1] = ((copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen + copy[i][j - 1].rgbtGreen + copy[i - 1][j - 1].rgbtGreen +
                               copy[i - 1][j].rgbtGreen + copy[i - 1][j + 1].rgbtGreen + copy[i + 1][j - 1].rgbtGreen + copy[i + 1][j].rgbtGreen +
                               copy[i + 1][j + 1].rgbtGreen) /
                              9);
                integar[2] = ((copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i - 1][j - 1].rgbtBlue +
                               copy[i - 1][j].rgbtBlue + copy[i - 1][j + 1].rgbtBlue + copy[i + 1][j - 1].rgbtBlue + copy[i + 1][j].rgbtBlue +
                               copy[i + 1][j + 1].rgbtBlue) /
                              9);

                floats[0] = ((copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed + copy[i][j - 1].rgbtRed + copy[i - 1][j - 1].rgbtRed +
                              copy[i - 1][j].rgbtRed + copy[i - 1][j + 1].rgbtRed + copy[i + 1][j - 1].rgbtRed + copy[i + 1][j].rgbtRed +
                              copy[i + 1][j + 1].rgbtRed) /
                             9.0);
                floats[1] = ((copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen + copy[i][j - 1].rgbtGreen + copy[i - 1][j - 1].rgbtGreen +
                              copy[i - 1][j].rgbtGreen + copy[i - 1][j + 1].rgbtGreen + copy[i + 1][j - 1].rgbtGreen + copy[i + 1][j].rgbtGreen +
                              copy[i + 1][j + 1].rgbtGreen) /
                             9.0);
                floats[2] = ((copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i - 1][j - 1].rgbtBlue +
                              copy[i - 1][j].rgbtBlue + copy[i - 1][j + 1].rgbtBlue + copy[i + 1][j - 1].rgbtBlue + copy[i + 1][j].rgbtBlue +
                              copy[i + 1][j + 1].rgbtBlue) /
                             9.0);

                for (int h = 0; h < 3; h++)
                {
                    if (floats[h] - integar[h] >= 0.5)
                    {
                        integar[h]++;
                    }
                    if (integar[h] > 255)
                    {
                        integar[h] = 255;
                    }
                }

                image[i - 1][j - 1].rgbtRed = integar[0];
                image[i - 1][j - 1].rgbtGreen = integar[1];
                image[i - 1][j - 1].rgbtBlue = integar[2];
            }
        }
    }
    return;
}

void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height + 2][width + 2];

    int ci = 0;
    int cl = height + 1;
    for (int q = 0; q < height + 2; q++)
    {
        for (int w = 0; w < width + 2; w++)
        {
            if (q == 0)
            {
                copy[q][w].rgbtRed = 0;
                copy[q][w].rgbtGreen = 0;
                copy[q][w].rgbtBlue = 0;
            }

            if (q == height + 1)
            {
                copy[q][w].rgbtRed = 0;
                copy[q][w].rgbtGreen = 0;
                copy[q][w].rgbtBlue = 0;
            }
        }
        copy[q][ci].rgbtRed = 0;
        copy[q][ci].rgbtGreen = 0;
        copy[q][ci].rgbtBlue = 0;
        copy[q][cl].rgbtRed = 0;
        copy[q][cl].rgbtGreen = 0;
        copy[q][cl].rgbtBlue = 0;
    }

    for (int k = 1; k < height + 1; k++)
    {
        for (int l = 1; l < width + 1; l++)
        {
            copy[k][l] = image[k - 1][l - 1];
        }
    }

    int Gxi[3];
    int Gyi[3];
    int Gfinali[3];
    float Gfinalf[3];

    for (int i = 1; i < height + 1; i++)
    {
        for (int j = 1; j < width + 1; j++)
        {
            Gxi[0] = (copy[i][j].rgbtRed * 0 + copy[i][j + 1].rgbtRed * 2 + copy[i][j - 1].rgbtRed * (-2) +
                      copy[i - 1][j - 1].rgbtRed * (-1) + copy[i - 1][j].rgbtRed * 0 + copy[i - 1][j + 1].rgbtRed * 1 +
                      copy[i + 1][j - 1].rgbtRed * (-1) + copy[i + 1][j].rgbtRed * 0 + copy[i + 1][j + 1].rgbtRed * 1);
            Gxi[1] = (copy[i][j].rgbtGreen * 0 + copy[i][j + 1].rgbtGreen * 2 + copy[i][j - 1].rgbtGreen * (-2) +
                      copy[i - 1][j - 1].rgbtGreen * (-1) + copy[i - 1][j].rgbtGreen * 0 + copy[i - 1][j + 1].rgbtGreen * 1 +
                      copy[i + 1][j - 1].rgbtGreen * (-1) + copy[i + 1][j].rgbtGreen * 0 + copy[i + 1][j + 1].rgbtGreen * 1);
            Gxi[2] = (copy[i][j].rgbtBlue * 0 + copy[i][j + 1].rgbtBlue * 2 + copy[i][j - 1].rgbtBlue * (-2) +
                      copy[i - 1][j - 1].rgbtBlue * (-1) + copy[i - 1][j].rgbtBlue * 0 + copy[i - 1][j + 1].rgbtBlue * 1 +
                      copy[i + 1][j - 1].rgbtBlue * (-1) + copy[i + 1][j].rgbtBlue * 0 + copy[i + 1][j + 1].rgbtBlue * 1);

            Gyi[0] = (copy[i][j].rgbtRed * 0 + copy[i][j + 1].rgbtRed * 0 + copy[i][j - 1].rgbtRed * 0 +
                      copy[i - 1][j - 1].rgbtRed * (-1) + copy[i - 1][j].rgbtRed * (-2) + copy[i - 1][j + 1].rgbtRed * (-1) +
                      copy[i + 1][j - 1].rgbtRed * (1) + copy[i + 1][j].rgbtRed * 2 + copy[i + 1][j + 1].rgbtRed * 1);
            Gyi[1] = (copy[i][j].rgbtGreen * 0 + copy[i][j + 1].rgbtGreen * 0 + copy[i][j - 1].rgbtGreen * 0 +
                      copy[i - 1][j - 1].rgbtGreen * (-1) + copy[i - 1][j].rgbtGreen * (-2) + copy[i - 1][j + 1].rgbtGreen * (-1) +
                      copy[i + 1][j - 1].rgbtGreen * (1) + copy[i + 1][j].rgbtGreen * 2 + copy[i + 1][j + 1].rgbtGreen * 1);
            Gyi[2] = (copy[i][j].rgbtBlue * 0 + copy[i][j + 1].rgbtBlue * 0 + copy[i][j - 1].rgbtBlue * 0 +
                      copy[i - 1][j - 1].rgbtBlue * (-1) + copy[i - 1][j].rgbtBlue * (-2) + copy[i - 1][j + 1].rgbtBlue * (-1) +
                      copy[i + 1][j - 1].rgbtBlue * (1) + copy[i + 1][j].rgbtBlue * 2 + copy[i + 1][j + 1].rgbtBlue * 1);

            for (int e = 0; e < 3; e++)
            {
                Gfinali[e] = sqrt((Gxi[e] * Gxi[e]) + (Gyi[e] * Gyi[e]));
                Gfinalf[e] = sqrt((Gxi[e] * Gxi[e]) + (Gyi[e] * Gyi[e]));
            }

            for (int h = 0; h < 3; h++)
            {
                if (Gfinalf[h] - Gfinali[h] >= 0.5)
                {
                    Gfinali[h]++;
                }
                if (Gfinali[h] > 255)
                {
                    Gfinali[h] = 255;
                }
            }

            image[i - 1][j - 1].rgbtRed = Gfinali[0];
            image[i - 1][j - 1].rgbtGreen = Gfinali[1];
            image[i - 1][j - 1].rgbtBlue = Gfinali[2];
        }
    }
    return;
}