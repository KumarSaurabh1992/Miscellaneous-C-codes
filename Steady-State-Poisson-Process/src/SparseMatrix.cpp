



#include "SparseMatrix.h"
//! Allocates the size of the sparse matrix
/*! @param N size to be allocated for sparse matrix*/
void SparseMatrix::initialize(int N){
	number_of_rows= N;
	Elements.set_size(N);
	I.set_size(N + 1);
	J.set_size(N);
	I.initialize();
	number_of_non_zero = 0;
	size_of_array = N;

}

//! Reads the data from the keyboard and stores in the sparse matrix
void SparseMatrix::get_data(){
	double temp;
	I[0] = 0;
	for(int i = 0; i < number_of_rows; i++){
		for(int j = 0; j < number_of_rows;j++){
			cin >> temp;

			if(temp){
				if (number_of_non_zero >= size_of_array){
//					cout << "Exceed" << endl;
					Elements.resize(2*number_of_non_zero);
					J.resize(2*number_of_non_zero);
					size_of_array = 2*number_of_non_zero;
				}
				Elements[number_of_non_zero] = temp;
				J[number_of_non_zero] = j;
				number_of_non_zero++;
//				cout << number_of_non_zero <<endl;
//				cout << size_of_array << endl;
			}
		}
		I[i + 1] = number_of_non_zero;
	}
	Elements.resize(number_of_non_zero + 1);
	J.resize(number_of_non_zero + 1);

}
//! Display the sparse matrix
void SparseMatrix::display(){
//	for (int i = 0; i < number_of_non_zero; i++){
//		cout << Elements.A[i] << "\t" << J.A[i] << endl;
//	}
//	for (int i = 0; i < number_of_rows; i++){
//			cout << I.A[i] << endl;
//	}
	for(int i = 0; i < number_of_rows; i++){
		for(int j = 0; j < number_of_rows; j++){
			cout << getValue(i,j) << "\t";
		}
		cout << endl;
	}


}

//! Returns the value at any particular location of the matrix A
//! @param m Row number
//! @param n Column number
//! @return A[m][n]
double SparseMatrix::getValue(int m, int n){
	for(int i = I[m]; i < I[m + 1]; i++){
		if (J[i] == n){
			return Elements[i];
		}
	}
	return 0;

}

//! Operator overloaded
/*! Multiply matrix  with a vector */
/*! Matrix A is in sparse form*/
/*! @param vec Vector */
/*! @return Vector */
Vector<double> SparseMatrix::operator * (Vector<double> vec){
	Vector<double> C;
	int row,col;
	C.set_size(number_of_rows);
	C.initialize();
	for(int i = 0; i < number_of_rows; i++){
		row = i;
		for(int j = I[i]; j < I[i + 1]; j++){
			col = J[j];
			C[row] += Elements[j]*vec[col];
		}
	}
	return C;
}
//! @return the number of rows
int SparseMatrix::get_row_size(){
	return number_of_rows;
}

//! @return the number of non-zero enteries
int SparseMatrix::get_non_zero_enteries(){
	return number_of_non_zero;
}

//! @return the total size of the sparse matrix
int SparseMatrix::get_size(){
	return size_of_array;
}

//! @param i the index of the location
//! @return the non-zero entry at location i
 double SparseMatrix::get_non_zero_Elements(int i){
	return Elements[i];
}

 //! @param i Row number
 /*! @return the number of non zero enteries before a particular row number*/
 int SparseMatrix::get_I(int i){
	return I[i];
}

 //! @param i the index of the location
 //! @return the column number at location i
int SparseMatrix::get_J(int i){
	return J[i];
}

//! Display I vector
void SparseMatrix::display_I(){
	for (int i = 0; i <= number_of_rows; i++){
		cout << I[i] << "\t";
	}
}

//! Display J vector
void SparseMatrix::display_J(){
	for (int i = 0; i < number_of_non_zero;i++){
		cout << J[i] << "\t";
	}
}

//! Update the matrix whenever a non zero entry comes.
/*! @param ROW Row number*/
/*! @param COL column number*/
/*! @param temp the value to be stored at (ROW,COL)*/

void SparseMatrix::update_matrix(double temp, int ROW, int COL){
	if(temp != 0){
		if (number_of_non_zero >= size_of_array){
	//					cout << "Exceed" << endl;
		 	Elements.resize(2*number_of_non_zero);
			J.resize(2*number_of_non_zero);
			size_of_array = 2*number_of_non_zero;
		}
			Elements[number_of_non_zero] = temp;
			J[number_of_non_zero] = COL;
			number_of_non_zero++;
	//				cout << number_of_non_zero <<endl;
	//				cout << size_of_array << endl;
		}
	I[ROW + 1] = number_of_non_zero;

}

//! resize the matrix when number of non-zero element exceeds the size of vector
void SparseMatrix::resize_matrix(){
	Elements.resize(number_of_non_zero + 1);
	J.resize(number_of_non_zero + 1);
//	cout << "Resize performed";
}

//! Multiplication of a matrix with a vector
/*! @param vec Vector which is multiplied with the sparse matrix*/
/*! @param temp Resulting Vector of the multiplication*/
void SparseMatrix::multiply(Vector<double> &vec, Vector<double> &temp){
	int row,col;
//	cout << temp.get_size();
	temp.initialize();
	for(int i = 0; i < number_of_rows; i++){
			row = i;
			for(int j = I[i]; j < I[i + 1]; j++){
				col = J[j];
				temp[row] += Elements[j]*vec[col];
			}
		}
}
//! This copies the sparse matrix into anoother sparse matrix
/*! @param spm the sparse matrix which is to be copied.*/

void SparseMatrix::copy(SparseMatrix & spm){
//	cout << spm.get_row_size();
	I.set_size(spm.get_row_size() + 1);
	J.set_size(spm.get_non_zero_enteries());
	Elements.set_size(spm.get_non_zero_enteries());
	number_of_rows = spm.get_row_size();
//	cout << number_of_rows;
	number_of_non_zero = spm.get_non_zero_enteries();
	size_of_array = spm.get_size();
	for (int i = 0; i < spm.get_row_size() + 1;i++){
//		cout << "row";
		I[i] = spm.get_I(i);
	}
	for (int i = 0; i < spm.get_non_zero_enteries();i++){
//		cout << "volumn";
		J[i] = spm.get_J(i);
	}
	for (int i = 0; i < spm.get_non_zero_enteries(); i++){
//		cout << spm.get_non_zero_Elements(i);
		Elements[i] = spm.get_non_zero_Elements(i);
//		cout << Elements[i];
	}

}
//! Extract diagonal for the preparation of Jacobi preconditioner
/*! @param spm Matrix A in Sparse form*/
void SparseMatrix::extractdiagonal(SparseMatrix & spm){
	for(int i = 0; i < spm.get_row_size(); i++){
		float temp = 1.0/spm.getValue(i,i);
		update_matrix(temp,i,i);
	}
}

//! Change the value of the matrix at (ROW,COL)
/*! @param temp new value */
/*! @param ROW Row number*/
/*! @param COL Column number*/

void SparseMatrix::update_matrix_ILU(double temp, int ROW, int COL){
	for(int i = I[ROW]; i < I[ROW + 1]; i++){
		if (J[i] == COL){
			Elements[i] = temp;
		}
	}
}
