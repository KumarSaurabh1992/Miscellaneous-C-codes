///*
// * SparseMatrix.cpp
// *
// *  Created on: Jan 29, 2015
// *      Author: saurabh
// */
//
//#include "SparseMatrix.h"
//
//Sparse_Matrix::Sparse_Matrix(int N) {
//	// TODO Auto-generated constructor stub
//	size = N;
//	number_non_zero = 1;
//	counter = 0;
//	A = new float[1];
//	I = new int[size];
//	J = new int[1];
//}
//
//void Sparse_Matrix::getData(){
//	float temp;
//	I[0] = 0;
//	for (int i = 0; i < size; i++){
//		for(int j = 0; j < size; j++){
//			cin >> temp;
//			if(temp){
//				if(counter < number_non_zero){
//					J[counter] = j;
//					A[counter] = temp;
//					counter++;
//
//				}
//				else{
//					resize();
//				}
//			}
//		}
//	}
//
//
//}
//
//void Sparse_Matrix::resize(){
//	counter = 2*number_non_zero;
//	float *temp = new float[counter];
//
//
//}
//
