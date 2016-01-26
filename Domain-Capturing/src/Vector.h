/*
 * Vector.h
 *
 *  Created on: Jan 17, 2015
 *      Author: saurabh
 */

#ifndef Vector_H_
#define Vector_H_
//#include "array.h"
#include <iostream>
using namespace std;

template <class T> class Vector {
	int elements;
	T *A;
	void getData();
	void initialize();
public:
	Vector<T>();
	Vector<T>(int m);
	~Vector<T>();
	void display();
	void read_values();
	void resize(int m);
	Vector operator + (Vector);
	Vector operator - (Vector);
	Vector operator * (Vector);

};

template <class T> Vector<T>::Vector(int m){
	elements = m;
	A = new T[m];
}

template <class T> Vector<T>:: Vector(){
	elements = 0;
	A = new T[elements];
}
template <class T> Vector<T>:: ~Vector<T>(){

}

template <class T> void Vector<T>::read_values(){
	getData();
}

template <class T> void Vector<T>::display()
{
	for (int i = 0; i < elements; i++)
		{
				cout<< A[i] << "\t";


		}
	cout << endl;

}

template <class T> void Vector<T>::getData()
{
	cout << "Enter the value for the vectors" << endl;
		for(int j = 0; j < elements; j++)
		{
			cin>> A[j];
		}
}


template <class T> Vector<T> Vector<T>::operator + (Vector vector2){
	Vector<T> temp_vector(elements);
			for(int j = 0; j < elements; j++)
			{
				temp_vector.A[j] = A[j] + vector2.A[j];

			}

	return (temp_vector);
}
template <class T> Vector<T> Vector<T>::operator - (Vector vector2){
	Vector<T> temp_matrix(elements);
			for(int j = 0; j < elements; j++)
			{
				temp_matrix.A[j] = A[j] - vector2.A[j];

			}

	return (temp_matrix);
}

template <class T> Vector<T> Vector<T>::operator * (Vector vector2){
	Vector<T> temp_vector(elements);
	temp_vector.initialize();
	for(int i = 0; i < elements; i++)
	{
		temp_vector.A[i] = A[i]*vector2.A[i];
	}

	return (temp_vector);
}
//template <class T> void Vector<T>::add(Vector matrix2)
//{
//	matrix1
//}

template <class T> void Vector<T> :: initialize(){
	for (int i = 0; i < elements; i++){
			A[i] = 0;

	}
}

template <class T> void Vector<T>::resize(int m){
	Vector<T> temp_vector(m);
	for(int i = 0; i < elements; i++){
		temp_vector.A[i] = A[i];
	}
	*A = *temp_vector.A;
	elements = m;

}
#endif /* Vector_H_ */
