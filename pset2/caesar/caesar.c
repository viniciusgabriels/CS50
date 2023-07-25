#include<stdio.h>
#include<cs50.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>

bool only_digits(string s);

char rotate(char c, int i);

int main(int argc, string argv[])
{
    // initial verifications
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    bool digit = only_digits(argv[1]);
    if (digit == false)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    int key = atoi(argv[1]);

    // user input
    string plaintext = get_string("plaintext: ");

    // cipher
    char ciphertext[strlen(plaintext)];
    for (int i = 0; i < strlen(plaintext); i++)
    {
        ciphertext[i] = rotate(plaintext[i], key);
    }
    printf("ciphertext:");

    for (int i = 0; i < strlen(plaintext); i++)
    {
        printf("%c", ciphertext[i]);
    }
    printf("\n");

}

// check numbers
bool only_digits(string s)
{
    int length = strlen(s);
    for (int i = 0; i < length; i++)
    {
        if ((isdigit(s[i])) == 0)
        {
            return false;
        }
    }
    return true;
}

// check upper/lower
char rotate(char c, int i)
{
    if ((isalpha(c)) == 0)
    {
        return c;
    }

    int character = 0;
    int alphaindex = 0;

    int formula = 0;

    int lower = islower(c);

    char upper = toupper(c);

    alphaindex = (int)upper - (int)'A';
    formula = (alphaindex + i) % 26;
    character = formula + (int)'A';
    char ch = (char)character;

    if (lower != 0)
    {
        ch = tolower((char)character);
    }
    return ch;
}