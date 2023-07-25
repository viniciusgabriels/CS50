#include <stdio.h>
#include <cs50.h>
#include <stdbool.h>

// calculate checksum for a valid card
bool validateCard(long int cardNumber)
{
    int digit, sum = 0, index = 1;

    while (cardNumber > 0)
    {
        digit = cardNumber % 10;
        cardNumber /= 10;

        if (index % 2 == 0)
        {
            digit *= 2;
            sum += digit % 10 + digit / 10;
        }
        else
        {
            sum += digit;
        }
        index++;
    }

    // Check the sum is multiple of 10
    return (sum % 10 == 0);
}

int main()
{
    // prompt for input
    long int cardNumber = get_long("Card number: ");

    // verifies the lenght of card number
    if (cardNumber < 1000000000000 || cardNumber >= 10000000000000000)
    {
        printf("INVALID\n");
        return 0;
    }

    // check for card lenght and starting digits to determinate the company
    // print AMEX, MASTERCARD, VISA, or INVALID
    if (validateCard(cardNumber))
    {
        if ((cardNumber >= 340000000000000 && cardNumber < 350000000000000) ||
            (cardNumber >= 370000000000000 && cardNumber < 380000000000000))
        {
            printf("AMEX\n");
            return 0;
        }
        else if (cardNumber >= 5100000000000000 && cardNumber < 5600000000000000)
        {
            printf("MASTERCARD\n");
            return 0;
        }
        else if ((cardNumber >= 4000000000000 && cardNumber < 5000000000000) ||
                 (cardNumber >= 4000000000000000 && cardNumber < 5000000000000000))
        {
            printf("VISA\n");
            return 0;
        }
    }

    printf("INVALID\n");
    return 0;
}