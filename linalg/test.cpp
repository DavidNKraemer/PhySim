#include <stdio.h>
#include "matrix.h"

int 
main ()
{
	printf("test.cpp\n");

	Matrix A = eye (3) * 2;
	Matrix B = ones (3, 5);

	(A*B).print();
	return 0;
}
