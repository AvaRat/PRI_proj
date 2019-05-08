#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

/*
2. Przeszukiwanie binarne. Napisać rekurencyjną funkcje szukającą zadanego elementu w tablicy liczb
całkowitych przy założeniu, że elementy tablicy są posortowane od najmniejszego do największego. Funkcja
ma dzielić aktualną tablicę na dwie części a następnie rekurencyjnie przeszukiwać tylko tą część, w której
szukany element na pewno występuje (należy pamiętać, że tablica jest posortowana). Ocenić złożoność
algorytmu
*/

int binary_search(int *tab, int begin, int end, int wanted_value)
{

  int divider = begin + (end-begin)/2;
  int middle_value = tab[divider];

  printf("%d\n", middle_value);

  if(divider-begin == 0)
  {
    if(middle_value == wanted_value)
      return divider;
    else return -1;
  }
  int index = -1;
  if(middle_value < wanted_value)
    index = binary_search(tab, divider, end, wanted_value);
  else 
  if(middle_value > wanted_value)
    index = binary_search(tab, begin, divider, wanted_value);
  else
    index =  divider;

  return index;
}



int main(int argc, char **argv)
{
  srand(time(NULL));
  int searched_val = 0;

  printf("searched value = ");
  scanf("%d", &searched_val);
  int tab[20];
  for(int i=0; i < 20; ++i)
  {
    tab[i] = rand() % 10;
    printf("%d ", tab[i]);
  }
  printf("\n");

  int result = binary_search(tab, 0, 14, searched_val);
  printf("result = %d\n", result);
  return 0;
}


