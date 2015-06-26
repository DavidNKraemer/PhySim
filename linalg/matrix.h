#ifndef MATRIX_H
#define MATRIX_H

/******************************************************
 *	Matrix class header file (includes signatures)    *
 *                                                    *
 *  Author: David Kraemer (kraemerd17)                *
 *  Modified: June 26 2015                            *
 ******************************************************/

class Matrix
{
private:
	void resize (int n);
	inline void set_array (double * arr, int len);
public:
	double * array; // double array to store the actual array data

	int size;
	int shape[2]; // integer array to store the shape of the matrix

	/* Various common ways to initialize matrices */
	Matrix (int m, int n, double * arr);
	Matrix (int m, int n);

	void reshape (int new_m, int new_n);
	void set_val (int i, int j, double val);
	void print (int precision = 2);

	Matrix transpose ();
	Matrix T ();

	/* Matrix arithmetic operations */
	Matrix operator+ (Matrix const M) const;
	Matrix operator- (Matrix const M) const;
	Matrix operator* (Matrix const M) const;
	Matrix operator* (double const c) const;
	Matrix operator/ (double const c) const;
	

	void operator+= (Matrix const M);
	void operator-= (Matrix const M);
	void operator*= (Matrix const M);
	void operator*= (double const c);
	void operator/= (double const c);
};

Matrix fill (int m, int n, double val);
Matrix fill (int n, double val);

Matrix eye (int n);
Matrix zeros (int m, int n);
Matrix zeros (int n);
Matrix ones (int m, int n);
Matrix ones (int n);

#endif