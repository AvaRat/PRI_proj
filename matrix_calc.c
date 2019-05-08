#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<math.h>

/*
kalkulator macierzowy oparty o tablice
dostępne operacje:
-transponowanie
-mnożenie przez skalar
-liczenie wyznacznika
-odwracanie
*/

typedef struct mat {
  unsigned int n_rows;
  unsigned int n_cols;
  float **matrix;
}Matrix;

void free_matrix(Matrix mat)
{
  for(int i=0; i<mat.n_rows; i++)
  {
    free(mat.matrix[i]);
  }
  free(mat.matrix);
}

void print_matrix(Matrix mat, char name[30])
{
  printf("%s\n", name);
  for(int row=0; row < mat.n_rows; row++)
  {
    for(int col=0; col < mat.n_cols; col++)
    {
      printf("%f ", mat.matrix[row][col]);
    }
    printf("\n");
  }
}

Matrix create_matrix(int n_rows, int n_cols)
{
  Matrix mat;
  mat.matrix = malloc(n_rows*sizeof(float*));
  mat.n_rows = n_rows;
  mat.n_cols = n_cols;
  for(int i=0; i< n_rows; i++)
    mat.matrix[i] = malloc(n_cols*sizeof(float));

  return mat;
}

void initialise_zeros(Matrix mat)
{
  float **target = mat.matrix;
  for(int r=0; r<mat.n_rows; r++)
  {
    for(int c=0; c<mat.n_cols; c++)
    {
      target[r][c] = 0;
    }
  }
}

void initialise_like(const Matrix old, Matrix new)
{
  if(old.n_cols != new.n_cols || old.n_rows != new.n_rows)
  {
    printf("dimensions must be the same to initialise\n");
    exit(EXIT_FAILURE);
  }
  float **mat = old.matrix;
  float **target = new.matrix;
  for(int r=0; r<old.n_rows; r++)
  {
    for(int c=0; c<old.n_cols; c++)
    {
      target[r][c] = mat[r][c];
    }
  }
}

Matrix gaussian_eliminate(Matrix mat)
{
  int n_rows = mat.n_rows;
  int n_cols = mat.n_cols;
  float **matrix = mat.matrix;

  if(n_rows != n_cols)
  {
    printf("macierz musi byc kwadratowa!!\n");
    exit(EXIT_FAILURE);
  }
  Matrix result_mat = create_matrix(n_rows, n_cols);
  initialise_like(mat, result_mat);
  float **tmp = result_mat.matrix;

  int c = 0;
  for(; c<n_cols; c++)
  {
    int r;
    for(r=c+1; r<n_rows; r++)
    {
      float L = tmp[r][c]/tmp[c][c];
      //Wn = Mat(n, col:n_cols);
      for(int i=c; i<n_cols; i++)
      {
        tmp[r][i] = tmp[r][i] - L*tmp[c][i];
      }
    //  result_mat.matrix[r][c] = L;
    }
  }
  return result_mat;
}

Matrix invert(const Matrix mat)
{
  int n_rows = mat.n_rows;
  int n_cols = mat.n_cols;
  float **matrix = mat.matrix;

  if(n_rows != n_cols)
  {
    printf("macierz musi byc kwadratowa!!\n");
    exit(EXIT_FAILURE);
  }

  Matrix result_mat = create_matrix(n_rows, n_cols);
  Matrix B = create_matrix(n_rows, n_cols);
  initialise_zeros(B);

  for(int i=0; i<B.n_cols; i++)
  {
    B.matrix[i][i] = 1;
  }

  initialise_like(mat, result_mat);

  float **tmp = result_mat.matrix;
  float **B_tmp = B.matrix;
  int c = 0;

// pierwsza iteracjia, z góry do dołu
  for(; c<n_cols; c++)
  {
    int r;

    for(r=c+1; r<n_rows; r++)
    {
      float L = tmp[r][c]/tmp[c][c];

      for(int i=c; i<n_cols; i++)
      {
        tmp[r][i] = tmp[r][i] - L*tmp[c][i]; 
      }
      for(int i=0; i<n_cols; i++)
        B_tmp[r][i] = B_tmp[r][i] - L*B_tmp[c][i];
    }
  }
  
// druga iteracja, od dołu do góry
  for(c=n_cols-1; c>0; c--)
  {
    int r;

    for(r=c-1; r>=0; r--)
    {
      float L = tmp[r][c]/tmp[c][c];

      for(int i=c; i>=0; i--)
      {
        tmp[r][i] = tmp[r][i] - L*tmp[c][i];
      }

      for(int i=0; i<n_cols; i++)
        B_tmp[r][i] = B_tmp[r][i] - L*B_tmp[c][i]; 
    }
  }

 // mnożymy wiersze, aby po lewej były same "1" na diagonali
  for(c=0; c<n_cols; c++)
  {
    float L = 1 / tmp[c][c];
    tmp[c][c] *= L;

    for(int r=0; r<n_rows; r++)
      B_tmp[c][r] *= L;
  } 

  free_matrix(result_mat);
  return B;
}

float det(const Matrix mat)
{
  Matrix m = gaussian_eliminate(mat);
  float **matrix = m.matrix;
  if(m.n_cols != m.n_rows)
  {
    printf("n_rows != n_cols\n");
    exit(EXIT_FAILURE);
  }
  float val = 1;
  for(int i=0; i < m.n_rows; i++)
  {
    val *=matrix[i][i];
  }
  return val;
}

Matrix transpose(Matrix mat)
{
  int n_rows = mat.n_rows;
  int n_cols = mat.n_cols;
  Matrix new_mat = create_matrix(n_cols, n_rows);
  float **new_matrix = new_mat.matrix;
  float **matrix = mat.matrix;
  for(int r=0; r<n_rows; r++)
  {
    for(int c=0; c<n_cols; c++)
    {
      new_matrix[c][r] = matrix[r][c];
    }
  }
  return new_mat;
}

void scalar_multiply(Matrix mat, float scalar)
{
  for(int i=0; i<mat.n_rows; i++)
  {
    for(int j=0; j<mat.n_cols; j++)
      {
        mat.matrix[i][j] *= scalar;
      }
  }
}

Matrix create_from_file(char path[50])
{
  FILE *fp;

  if ((fp=fopen(path, "r"))==NULL) 
  {
    printf ("Cannot open file!\n");
    exit(EXIT_FAILURE);
  }

  int max_matrix_size = 10;
  float x = 0.0f;
  char ch;
  float *row = malloc(max_matrix_size*sizeof(float));
  float **matrix = malloc(max_matrix_size*sizeof(float*));


  int n_row = 0;
  int previous_n_col = 0;
  bool first_iter = true;
  int n_col = 0;
  int n_received = 0;
  while(feof(fp) == 0)
  {
    n_received  = fscanf(fp, "%f%c", &x, &ch);
    row[n_col++] = x;

    if(ch == '\n' || n_received == 1)
    {
      //printf("%f\n", row[n_col-1]);
      if(n_col != previous_n_col && first_iter==false)
      {
        printf("ERROR wrong matrix format\n");
        exit(EXIT_FAILURE);
      }
      matrix[n_row] = malloc(n_col*sizeof(float));
      first_iter = false;

      for(int i=0; i<n_col; i++)
        matrix[n_row][i] = row[i];
      n_row++;
      previous_n_col = n_col;
      n_col = 0;
    }
  }

  free(row);
  fclose(fp);

  Matrix mat = {n_row, previous_n_col, matrix}; 
  return mat;
}

int main(int argc, char *argv)
{
  char path[] = "/home/marcel/Documents/Programming/cpp_learning/PRI/PRI_proj/mat_1.txt";
  Matrix mat = create_from_file(path);
  printf("rows = %d\tcols = %d\n", mat.n_rows, mat.n_cols);
  print_matrix(mat, "normal");
  Matrix mat_ = transpose(mat);
  print_matrix(mat_, "transposed");
  scalar_multiply(mat, 2.0);
  print_matrix(mat, "multiplied");
  free_matrix(mat);
  free_matrix(mat_);
}