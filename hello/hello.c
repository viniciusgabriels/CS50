#include <stdio.h>
#include <cs50.h>

int main(void)

{
    string name = get_string("Informe o seu nome: \n");
    printf("hello, %s \n", name);
}