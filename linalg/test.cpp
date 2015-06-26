#include <stdio.h>
#include "matrix.h"

/******************************************************
 *	Matrix class test file (includes main method)     *
 *                                                    *
 *  Author: David Kraemer (kraemerd17)                *
 *  Modified: June 26 2015                            *
 ******************************************************/

int 
main ()
{
	printf("test.cpp\n");

	Matrix A = eye (2) * 2;
	Matrix B = ones (2, 1);

	A *= B;
	A.print();

	return 0;
}
