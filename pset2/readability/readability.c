#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

// input: "Text:" com get_string
// espaços: isspace()
// pontuações: ispunct()
// All punctuation characters in C programming are:
// ! " # $ % & ' ( ) * +, - . / : ;  ? @ [ \ ] ^ _ ` { | } ~

int main(void)
{
    int letters = 0;
    int words = 1;
    int sentences = 0;

    string text = get_string("Text: ");

    int stringLength = strlen(text);

    for (int i = 0; i < stringLength; i++)
    {
        if ((tolower(text[i]) >= 'a' && tolower(text[i]) <= 'z'))
        {
            letters++;
        }
        if (text[i] == ' ')
        {
            words++;
        }
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentences++;
        }
    }

    float L = (((float)letters / (float)words) * 100);
    float S = (((float)sentences / (float)words) * 100);

    int ColemanLiauIndex = round(0.0588 * L - 0.296 * S - 15.8);

    if (ColemanLiauIndex < 1)
    {
        printf("\nBefore Grade 1\n");
    }
    else if (ColemanLiauIndex > 16)
    {
        printf("\nGrade 16+\n");
    }
    else
    {
        printf("Grade %i\n", ColemanLiauIndex);
    }

    return 0;
}

// letters = conta tudo menos espaços e exclamações
// words = conta a cada espaço no texto
// sentences = conta a cada ponto final, exclamação ou interrogação

// ColemanLiauIndex = 0.0588 * L - 0.296 * S - 15.8
// L = média de letras a cada 100 palavras
// S = média de palavras a cada 100 sentenças

// Grade deve ser arredondado do >= .5 pra cima e < .5 pra baixo
// Grade menor que 1 deve responder "Before Grade 1"
// Grade maior que 16 deve responder "Grade 16+"