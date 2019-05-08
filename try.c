#include <stdio.h>
#include<math.h>

typedef struct mat {
  unsigned int n_rows;
  unsigned int n_cols;
  float **matrix;
}Matrix;


int main(void)
{
  float *tab2d = malloc(5*sizeof(float));
  Matrix mat = {1, 1, tab2d};
  
  return 0;
}