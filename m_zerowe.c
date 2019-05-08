#include <stdio.h>
#include <stdlib.h>
#include <math.h>




// ax^b + cx^d + ex^f + g
typedef struct f {
  double a;
  double b;
  double c;
  double d;
  double e;
  double f;
  double g;
}Function;

void print_f(Function f)
{
  printf("f(x) = %gx^%g + %gx^%g + %gx^%g + %g\n", f.a, f.b, f.c, f.d, f.e, f.f, f.g);
}

// gets the value of f in point x
double f(Function f, double x)
{
//  Function f = {1, 2, 3, 5, 0, 2, 8};

  return (f.a*pow(x, f.b) + f.c*pow(x,f.d) + f.e*pow(x,f.f) + f.g);
}

double bisekcja(Function fun, double left, double right, double eps)
{
  double a = left;
  double b = right;
  double x = 0;
  //sprawdzenie, czy na przedziale jest miejsce zerowe
  if(f(fun, a)* f(fun, b) > 0)
  {
    printf("****ERROR*****\n**funkcja nie musi mieć miejsca zerowego na zadanym przedziale**\n");
    return -1;
  }
  int iters = 0;
  while(fabs(a-b) > eps)
  {
  // /  printf("a = %f\tb = %f\n", a, b);
    x = (a+b)/2;
    double val = f(fun, x);
    if(fabs(val) <= eps)
    {
      break;
      printf("break\n");
    }
    else if(val * f(fun, a) < 0)
      b = x;
    else
      a = x; 
    ++iters;
   // printf("k\n");
  //  printf("abs(a-b) = %f\n", fabs(a-b));
  }
  printf("nr of iterations: %d\n", iters);
  
  return (a+b)/2;
}

int main(void)
{
  Function f1 = {-9, 3, 100, 2, 90, 1, 0};

  print_f(f1);
  double x = 0;
  double eps = 1e-12;
  x = bisekcja(f1, 5, 30, eps);
  printf("miejsce zerowe = %f\n", x);
}
