#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

int 
main ()
{
	printf("test.cpp\n");

	Matrix A = ones (6);

	A.print();

	A.reshape(3,12);

	A.print();

	return 0;
}
