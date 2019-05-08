matrix_calc : matrix_calc.o
	cc -std=c11 -Wall -o matrix_calc matrix_calc.o -lm

matrix_calc.o : matrix_calc.c
	cc -c matrix_calc.c

clean : 
	rm matrix_calc.o matrix_calc