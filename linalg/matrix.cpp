#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matrix.h"

Matrix::Matrix (int m, int n, double * arr)
{
	shape[0] = m;
	shape[1] = n;
	size = m * n;

	array = new double [m*n];
	
	for (int i=0; i < size; i++)
		array[i] = arr[i];

	return;
}

void Matrix::reshape (int new_m, int new_n)
{
	if (size != new_m * new_n) return;

	shape[0] = new_m;
	shape[1] = new_n;

	return;
}

void Matrix::set_val (int i, int j, double val)
{
	array[shape[1] * i + j] = val;

	return;
}

void Matrix::print (int precision)
{
	for (int i=0; i<shape[0]; i++)
	{
		printf ("[");
		for (int j=0; j<shape[1]; j++)
		{
			printf ("%6.*lf", precision, array[shape[1] * i + j]);
		}
		printf ("  ]\n");
	}
}

Matrix fill (int m, int n, double val)
{
	double arr[m*n];
	for (int i=0; i<m*n; i++)
		arr[i] = val;

	return Matrix (m, n, arr);
}

Matrix fill (int n, double val)
{
	return fill (n, n, val);
}


Matrix zeros (int m, int n)
{
	return fill (m, n, 0.);
}

Matrix zeros (int n)
{
	return fill (n, 0.);
}

Matrix ones (int m, int n)
{
	return fill (m, n, 1.);
}

Matrix ones (int n)
{
	return fill (n, n, 1.);
}

Matrix eye (int n)
{
	Matrix A = zeros (n, n);
	for (int i=0; i<n; i++)
		A.set_val(i, i, 1.);

	return A;
}