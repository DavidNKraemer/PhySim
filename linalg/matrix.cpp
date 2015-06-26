#include <stdio.h>
#include "matrix.h"

/******************************************************
 *	Matrix class functions (specified by matrix.h)    *
 *                                                    *
 *  Author: David Kraemer (kraemerd17)                *
 *  Modified: June 26 2015                            *
 ******************************************************/


/**************** PRIVATE METHODS *********************
 *
 * These methods are designed to let public functions
 * resize and readjust the matrix internals as needed
 * without letting the user meddle with potentially
 * dangerous side effects.
 *
*******************************************************/
void 
Matrix::resize (int n)
/* Modifies th size field of the underlying matrix.     */
{
	size = n;
}

inline void
Matrix::set_array (double * arr, int len)
/* Modifies the array field of the underlying matrix.   */
{
	array = new double [len];
	
	for (int i=0; i < len; i++)
		array[i] = arr[i];

	return;
}

/**************** PUBLIC METHODS **********************/

Matrix::Matrix (int m, int n, double * arr)
/* Basic constructor. Specifies dimensions, and provides
   a desired array.
   @param int m: the 'height' (number of rows)
   @param int n: the 'width' (number of columns)
   @param double * arr: the desired array

   Many future constructors use this as the basic 
   framework for more specialized matrices.             */
{
	shape[0] = m;
	shape[1] = n;
	size = m * n;

	set_array (arr, size);
}

void 
Matrix::reshape (int new_m, int new_n)
/* Reshapes the matrix, requiring that the new shape 
   be compatible with the size of the underlying array.
   @param int new_m: the new 'height' (number of rows)
   @param int new_n: the new 'width' (number of cols)

   @return [Called for side effects]

   Postcondition: if new_m * new_n != size, no changes
   are made. (This is why resize is a private method; 
   if the shape of the matrix needs to change such that
   it is incompatible with the original size, there is 
   a sneaky way to accomplish this.)                    */

{
	if (size != new_m * new_n) return;

	shape[0] = new_m;
	shape[1] = new_n;

	return;
}

void 
Matrix::set_val (int i, int j, double val)
/* Manually changes the value of the (i,j)th entry
   of the matrix. 
   @param int i: the desired row
   @param int j: the desired column
   @param double val: the value to which the entry is set

   Note: i and j both are indexed from 0

   @return [Called for side effects]                    */
{
	array[shape[1] * i + j] = val;

	return;
}

void 
Matrix::print (int precision)
/* Writes the matrix to stdout in human-readable form.
   @param int precision: (optional, default=2) the 
   displayed floating-point precision 

	@return [Called for side effects]                   */
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
/* Generates an m-by-n matrix filled with a specific value.
   @param int m: the 'height' of the matrix (rows)
   @param int n: the 'width' of the matrix (columns)
   @param double val: the value given to each entry

   @return: a new matrix with desired properties.       */
{
	double arr[m*n];
	for (int i=0; i<m*n; i++)
		arr[i] = val;

	return Matrix (m, n, arr);
}

Matrix 
fill (int n, double val)
/* Generates an n-by-n matrix filled with a specific value.
   @param int n: the dimension of the matrix (row and col)
   @param double val: the value given to each entry

   @return: a new matrix with desired properties.       */
{
	return fill (n, n, val);
}


Matrix 
zeros (int m, int n)
/* Generates an m-by-n matrix filled with the number 0.
   @param int m: the 'height' of the matrix (rows)
   @param int n: the 'width' of the matrix (columns)

   @return: a new zero matrix.                          */
{
	return fill (m, n, 0.);
}

Matrix 
zeros (int n)
/* Generates an n-by-n matrix filled with the number 0.
   @param int n: the dimension of the matrix (row and col)

   @return: a new square zero matrix.                   */
{
	return fill (n, 0.);
}

Matrix 
ones (int m, int n)
/* Generates an m-by-n matrix filled with the number 1.
   @param int m: the 'height' of the matrix (rows)
   @param int n: the 'width' of the matrix (columns)

   @return: a new ones matrix.                          */
{
	return fill (m, n, 1.);
}

Matrix 
ones (int n)
/* Generates an n-by-n matrix filled with the number 1.
   @param int n: the dimension of the matrix (row and col)

   @return: a new square ones matrix.                   */
{
	return fill (n, n, 1.);
}

Matrix 
eye (int n)
/* Generates an n-by-n identity matrix.
   @param int n: the dimension of the matrix (row and col)

   @return: a new square identity matrix.               */
{
	Matrix A = zeros (n, n);
	for (int i=0; i<n; i++)
		A.set_val(i, i, 1.);

	return A;
}

Matrix 
Matrix::transpose ()
/* Generates the transpose of a given matrix.
   @return: the matrix transpose                        */
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

	return Matrix(shape[1], shape[0], tran_arr);
}

Matrix 
Matrix::T ()
/* Handy shorthand for the matrix transpose function.
   @return: the matrix transpose                        */
{
	return transpose();
}

Matrix 
Matrix::operator+ (Matrix const M) const
/* Overloaded matrix sum operator
   @param Matrix const M: the second summand

   @return: the matrix sum of the current matrix and M. */
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
/* Overloaded matrix subtraction operator
   @param Matrix const M: the second summand

   @return: the matrix difference of the current matrix 
            and M.                                      */
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
/* Overloaded matrix-scalar product operator
   @param double c: the scalar

   @return: the scaling of the current matrix by c      */
{
	double new_arr[size];
	for (int i=0; i<size; i++)
		new_arr[i] = array[i] * c;

	return Matrix(shape[0], shape[1], new_arr);	
}

Matrix 
Matrix::operator/ (double const c) const
/* Overloaded matrix-scalar quotient operator
   @param double c: the scalar

   @return: the inverse quotient of the current 
            matrix by c                                 */
{
	double new_arr[size];
	for (int i=0; i<size; i++)
		new_arr[i] = array[i] / c;

	return Matrix(shape[0], shape[1], new_arr);	
}

void 
Matrix::operator+= (Matrix const M)
/* Overloaded matrix addition assignment operator
   @param Matrix const M: the matrix whose sum is to be
   added.

   @return [Called for side effects]                    */ 

{
	if (shape[0] != M.shape[0] || shape[1] != M.shape[1])
		throw ( "Matrices are not aligned." );

	double new_arr[size];
	for (int i=0; i<size; i++)
		array[i] += M.array[i];

	return;
}

void 
Matrix::operator-= (Matrix const M)
/* Overloaded matrix subtraction assignment operator
   @param Matrix const M: the matrix whose sum is to be
   added.

   @return [Called for side effects]                    */ 
{
	if (shape[0] != M.shape[0] || shape[1] != M.shape[1])
		throw ( "Matrices are not aligned." );

	for (int i=0; i<size; i++)
		array[i] -= M.array[i];

	return;
}

void 
Matrix::operator*= (double const c)
/* Overloaded matrix scalar multiplication assignment 
   operator.
   @param double const c: the scalar multiple

   @return [Called for side effects]                    */ 
{
	double new_arr[size];
	for (int i=0; i<size; i++)
		array[i] *= c;

	return;
}

void 
Matrix::operator/= (double const c)
/* Overloaded matrix scalar division assignment 
   operator.
   @param double const c: the scalar multiple

   @return [Called for side effects]                    */ 
{
	double new_arr[size];
	for (int i=0; i<size; i++)
		array[i] /= c;

	return;
}

Matrix
Matrix::operator* (Matrix const M) const
/*  Overloaded matrix-matrix product operator
    @param Matrix const M: matrix to multiply with.

    @return: the matrix product between the current 
             matrix and the matrix M

    Note: this method uses the naive O(n^3) algorithm   */
{
	if (shape[1] != M.shape[0])
	/* Checks if the matrices are properly aligned */
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
				M_index = M.shape[1] * k + j;
				sum += array[index] * M.array[M_index];
			}

			new_index = M.shape[1] * i + j;
			new_array[new_index] = sum;
		}
	} // for

	return Matrix (shape[0], M.shape[1], new_array);
} 

void
Matrix::operator*= (Matrix const M)
/*  Overloaded matrix-matrix product assignment operator
    @param Matrix const M: matrix to multiply with.

    @return: [Called for its side effects]

    Note: this method uses the naive O(n^3) algorithm   */
{
	if (shape[1] != M.shape[0]) 
	/* Checks if the matrices are properly aligned */
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
				M_index = M.shape[1] * k + j;
				sum += array[index] * M.array[M_index];
			}

			new_index = M.shape[1] * i + j;
			new_array[new_index] = sum;
		}
	} // for

	resize (shape[0] * M.shape[1]);
	reshape (shape[0], M.shape[1]);
	set_array (new_array, size);
}