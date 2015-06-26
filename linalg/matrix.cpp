#include <stdio.h>
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

void 
Matrix::reshape (int new_m, int new_n)
{
	if (size != new_m * new_n) return;

	shape[0] = new_m;
	shape[1] = new_n;

	return;
}

void 
Matrix::set_val (int i, int j, double val)
{
	array[shape[1] * i + j] = val;

	return;
}

void 
Matrix::print (int precision)
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

Matrix 
fill (int m, int n, double val)
{
	double arr[m*n];
	for (int i=0; i<m*n; i++)
		arr[i] = val;

	return Matrix (m, n, arr);
}

Matrix 
fill (int n, double val)
{
	return fill (n, n, val);
}


Matrix 
zeros (int m, int n)
{
	return fill (m, n, 0.);
}

Matrix 
zeros (int n)
{
	return fill (n, 0.);
}

Matrix 
ones (int m, int n)
{
	return fill (m, n, 1.);
}

Matrix 
ones (int n)
{
	return fill (n, n, 1.);
}

Matrix 
eye (int n)
{
	Matrix A = zeros (n, n);
	for (int i=0; i<n; i++)
		A.set_val(i, i, 1.);

	return A;
}

Matrix 
Matrix::transpose ()
{
	double tran_arr[size];
	int a, b, i, j;
	for (a=0; a<size; a++)
	{
		j = a % shape[0];
		i = a / shape[0];
		b = j * shape[1] + i;
		tran_arr[a] = array[b];
	}

	return Matrix(shape[0], shape[1], tran_arr);
}

Matrix 
Matrix::T ()
{
	return transpose();
}

Matrix 
Matrix::operator+ (Matrix const M) const
{
	if (shape[0] != M.shape[0] || shape[1] != M.shape[1])
		throw ( "Matrices are not aligned." );

	double new_arr[size];
	for (int i=0; i<size; i++)
		new_arr[i] = array[i] + M.array[i];

	return Matrix(shape[0], shape[1], new_arr);
}

Matrix 
Matrix::operator- (Matrix const M) const
{
	if (shape[0] != M.shape[0] || shape[1] != M.shape[1])
		throw ( "Matrices are not aligned." );

	double new_arr[size];
	for (int i=0; i<size; i++)
		new_arr[i] = array[i] - M.array[i];

	return Matrix(shape[0], shape[1], new_arr);
}

Matrix 
Matrix::operator* (double const c) const
{
	double new_arr[size];
	for (int i=0; i<size; i++)
		new_arr[i] = array[i] * c;

	return Matrix(shape[0], shape[1], new_arr);	
}

Matrix 
Matrix::operator/ (double const c) const
{
	double new_arr[size];
	for (int i=0; i<size; i++)
		new_arr[i] = array[i] / c;

	return Matrix(shape[0], shape[1], new_arr);	
}

void 
Matrix::operator+= (Matrix const M) const
{
	if (shape[0] != M.shape[0] || shape[1] != M.shape[1])
		throw ( "Matrices are not aligned." );

	double new_arr[size];
	for (int i=0; i<size; i++)
		array[i] += M.array[i];

	return;
}

void 
Matrix::operator-= (Matrix const M) const
{
	if (shape[0] != M.shape[0] || shape[1] != M.shape[1])
		throw ( "Matrices are not aligned." );

	for (int i=0; i<size; i++)
		array[i] -= M.array[i];

	return;
}

void 
Matrix::operator*= (double const c) const
{
	double new_arr[size];
	for (int i=0; i<size; i++)
		array[i] *= c;

	return;
}

void 
Matrix::operator/= (double const c) const
{
	double new_arr[size];
	for (int i=0; i<size; i++)
		array[i] /= c;

	return;
}

Matrix
Matrix::operator* (Matrix const M) const
/*
  Multiplies two matrices.
  If A is an (m,n) matrix and B is an (l,p)
  matrix, the computation ends if n != l.
  Otherwise, successful computation results
  in a third matrix C of shape (m,p).
*/
{
	if (shape[1] != M.shape[0]) // check if improperly aligned
	{
		throw ("Misaligned matrix");
	} // if

	double new_array[shape[0] * M.shape[1]];
	double sum;
	int index, M_index, new_index;

	for (int i=0; i < shape[0]; i++) 
	{ /* Loop through rows of this matrix */
		for (int j=0; j < M.shape[1]; j++)
		{
			sum = 0.;
			for (int k=0; k < M.shape[0]; k++)
			{
				index = shape[1] * i + k;
				M_index = M.shape[0] * k + j;
				sum += array[index] * M.array[M_index];
			}

			new_index = shape[1] * i + j;
			new_array[new_index] = sum;
		}


	} // for

	return Matrix (shape[0], M.shape[1], new_array);

} // dot