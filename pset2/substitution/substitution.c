#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

bool only_alpha(string s);
bool unique(string s);
char ciphered(char c, string s);

// get key
int main(int argc, string argv[])
{
    // validade key
    if (argc != 2)
    {
        printf("Usage: ./substitution key \n");
        return 1;
    }

    if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    bool alpha = only_alpha(argv[1]);
    if (alpha == false)
    {
        printf("Key must only contain alphabetic characters.\n");
        return 1;
    }

    bool u = unique(argv[1]);
    if (u == false)
    {
        printf("Key must not contain repeated characters.\n");
        return 1;
    }

    // get plaintext
    string plaintext = get_string("plaintext: ");

    // encipher
    char ciphertext[strlen(plaintext)];

    for (int i = 0; i < strlen(plaintext); i++)
    {
        ciphertext[i] = ciphered(plaintext[i], argv[1]);
    }
    // print ciphertext
    printf("ciphertext: ");

    for (int i = 0; i < strlen(plaintext); i++)
    {
        printf("%c", ciphertext[i]);
    }
    printf("\n");
}

bool only_alpha(string s)
{
    int length = strlen(s);
    for (int i = 0; i < length; i++)
    {
        if (isalpha(s[i]) == 0)
        {
            return false;
        }
    }
    return true;
}

bool unique(string s)
{
    char alpha[strlen(s)];
    for (int i = 0; i < strlen(s); i++)
    {
        alpha[i] = toupper(s[i]);
    }
    int length = strlen(s);
    for (int i = 0; i < length; i++)
    {
        for (int j = length; j > i; j--)
        {
            if (alpha[j] == alpha[i])
            {
                return false;
            }
        }
    }
    return true;
}

char ciphered(char c, string s)
{
    if (isalpha(c) == 0)
    {
        return c;
    }

    char alphabet[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    char key[26];

    for (int i = 0; i < strlen(s); i++)
    {
        key[i] = s[i];
    }

    int upper = isupper(c);
    char character = tolower(c);
    int index = 0;
    for (int i = 0; i < 26; i++)
    {
        if (character == alphabet[i])
        {
            index = i;
        }
    }

    char cipher;

    if (upper == 0)
    {
        cipher = tolower(key[index]);
    }
    else
    {
        cipher = toupper(key[index]);
    }
    return cipher;
}