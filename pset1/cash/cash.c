#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)

{
    int PENNY = 1;
    int NICKEL = 5;
    int DIME = 10;
    int QUARTER = 25;
    float changeOwed;
    do
    {
        changeOwed = get_float("Change owed: ");
    }
    while (changeOwed <= 0.00);

    int cents = round(changeOwed * 100);
    int numberOfCoins = 0;

    while (cents >= QUARTER)
    {
        cents = cents - QUARTER;
        numberOfCoins++;
    }
    while (cents >= DIME)
    {
        cents = cents - DIME;
        numberOfCoins++;
    }
    while (cents >= NICKEL)
    {
        cents = cents - NICKEL;
        numberOfCoins++;
    }
    while (cents >= PENNY)
    {
        cents = cents - PENNY;
        numberOfCoins++;
    }
    if (numberOfCoins > 1)
    {
        printf("%i Coins\n", numberOfCoins);
    }
    else
    {
        printf("%i Coin\n", numberOfCoins);
    }

}