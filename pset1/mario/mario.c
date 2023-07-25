#include <stdio.h>
#include <cs50.h>

// By giving bether names for variables, the code turns self-explanatory
int main(void)
{
    int numberOfLines;
    do
    {
        numberOfLines = get_int("Positive Number: ");
    }
    while (numberOfLines < 1 || numberOfLines > 8);

    for (int i = 0; i < numberOfLines; i++)
    {
        for (int j = 1; j < numberOfLines - i; j++)
        {
            printf(" ");
        }
        for (int k = 0; k <= i; k++)
        {
            printf("#");
        }
        printf("\n");
    }
}
