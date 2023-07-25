#include <stdio.h>
#include <cs50.h>

int main(void)
{
      // TODO: Solicite o valor inicial ao usuário
      int initialPopulation;
      int finalPopulation;
      do
      {
            initialPopulation = get_int("População inicial de Ilhamas: ");
      } while (initialPopulation < 9);

      // TODO: Solicite o valor final ao usuário
      do
      {
            finalPopulation = get_int("População final de Ilhamas: ");
      } while (finalPopulation < initialPopulation);

      // TODO: Calcule o número de anos até o limite
      int currentPopulation = initialPopulation;
      int years;
      for (years = 0; currentPopulation < finalPopulation; years++)
      {
            currentPopulation += (currentPopulation / 3) - (currentPopulation / 4);
      }

      // TODO: Imprima o número de anos
      printf("Years: %i\n", years);
}