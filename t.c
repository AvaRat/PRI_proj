#include "stdio.h"

void fun(char *word, int n, int m)
{
//  printf("in fun\n");
  int len = 0;
  char *ch = word;
  while(*ch++ != '\0')
    ++len;
  char *tmp = word;
  int i=0;
  for(;  n<=m;  n++, i++)
  {
    word[i] = tmp[n];
  }
  word[i] = '\0';

};

int main(void)
{
  char word[] = "marcelos.kali";
  fun(word, 2, 10);

  printf("result: %s\n", word);
  return 0;
}