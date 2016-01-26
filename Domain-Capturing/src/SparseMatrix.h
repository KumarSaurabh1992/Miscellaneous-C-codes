/*
 * SparseMatrix.h
 *
 *  Created on: Jan 29, 2015
 *      Author: saurabh
 */

#ifndef SPARSEMATRIX_H_
#define SPARSEMATRIX_H_
#include "Vector.h"

class Sparse_Matrix {
	int size;
	int number_non_zero;
	int counter;
	float* A;
	int* I;
	int* J;
public:
	Sparse_Matrix(int N);
	void getData();
	void initialize();
	void resize();

};

#endif /* SPARSEMATRIX_H_ */
