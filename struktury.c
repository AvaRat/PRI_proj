/*
5. Zaprojektować struktury (tablica struktur) służące do przechowywania informacji o osobach (imię,
nazwisko, pesel, wiek). Napisać funkcję wyliczającą średni wiek osoby.
*/

#include<stdio.h>

typedef struct person{
  int age;
  int pesel;
  char name[20];
  char surname[20];
} Person;


int main(void)
{
  /*
  Person tab[10];
  tab[0].age = 19;
  tab[0].pesel = 98011900917;
  tab[0].name = "macel";
  tab[0].surname = "kowalski";
*/
  printf("sizeof double = %ld\nsizeof double* = %ld\n", sizeof(double), sizeof(double*));

}