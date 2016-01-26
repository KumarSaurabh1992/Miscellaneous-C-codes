//! This class stores the value of matrix in sparse form
/*! @author Kumar Saurabh (MA14M004)*/

#ifndef SPARSEMATRIX_H_
#define SPARSEMATRIX_H_
#include "Vector.h"

class SparseMatrix {
	//! Vector containing the elements of the matrix A
	Vector <double> Elements;
	//! Vector containing the row information about the matrix A
	Vector <int> I;
	//! Vector containing the column information about the matrix A
	Vector <int> J;
	//! Number of rows in the sparse matrix
	int number_of_rows;
	//! Number of non-zero enteries in sparse matrix
	int number_of_non_zero;
	//! Size of the sparse matrix
	int size_of_array;

public:
	void initialize(int N);
	void get_data();
	void display();
	void display_I();
	void display_J();
	double getValue(int m, int n);
	int get_row_size();
	int get_non_zero_enteries();
	int get_size();
	void update_matrix(double m, int ROW, int COL);
	void set_size_I(int N);
	void set_size_J(int N);
	void resize_matrix();
	Vector<double> operator * (Vector<double> vec);
	double get_non_zero_Elements(int );
	int get_I(int );
	int get_J(int );
	void multiply(Vector<double> &, Vector<double> &);
	void copy(SparseMatrix & );
	void extractdiagonal(SparseMatrix &);
	void update_matrix_ILU(double , int, int );
};

#endif /* SPARSEMATRIX_H_ */
