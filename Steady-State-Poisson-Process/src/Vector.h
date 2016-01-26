//! This class computes the matrix of AX = B
/*! @author Kumar Saurabh (MA14M004)*/



#ifndef Vector_H_
#define Vector_H_
#include <iostream>
using namespace std;

template <class T> class Vector {
	//! number of elements in the vector
	int elements;
	//! Add the enteries into the vector
	void getData();
	//! 1D array to store data
	T * A;
	//	T getelement();
public:

	//! Default Constructor
	Vector<T>();
	//! Constructor
	/*! @param m creates a vector of size m*/
	Vector<T>(int m);
	//! Destructor
	~Vector<T>();
	//! Prints the value of vector
	void display();
	//! Initializes the vector with 0.
	void initialize();
	//! Reads the enteries from the user and stores in the vector
	void read_values();
	//! Resizes the vector
	/*! Does both the operation of increasing and decreasing the vector size*/
	/*! @param m the size of desired vector*/
	void resize(int m);
	//! Sets the vector size
	/*! @param m size of the vector*/
	void set_size(int m);
	//! @returns the size of the vector
	int get_size();

	Vector operator + (Vector &);
	Vector operator - (Vector);
	T operator * (Vector &);
	Vector operator * (float);
	void copy_values (Vector &);
	T & operator[] (int i);
	void del();
	void add(Vector &, Vector &, T);
	void sub(Vector &,Vector &);
	void add(Vector &,Vector &);
	void set_value(int , T);
	void multiply_dot(Vector &, Vector &);
	void ones();

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
	//	cout << "In destr" << endl;
	if (elements != 0){
		delete A;
		elements = 0;
	}
	//	cout << "Delete";
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
//! operator overloaded
/*! Computes the addition of two vectors A = vector1 + vector 2*/
/*! @param vector2 vector to be added with*/
/*! @return the vector A.*/

template <class T> Vector<T> Vector<T>::operator + (Vector &vector2){
	Vector<T> temp_vector(elements);
	for(int j = 0; j < elements; j++)
	{
		temp_vector.A[j] = A[j] + vector2.A[j];

	}
	//			cout <<"Hi in";

	return (temp_vector);
}
//! operator overloaded
/*! Computes the subtraction of two vectors A = vector1 - vector 2*/
/*! @param vector2 vector to be subtracted with*/
/*! @return the vector A.*/
template <class T> Vector<T> Vector<T>::operator - (Vector vector2){
	Vector<T> temp_matrix(elements);
	for(int j = 0; j < elements; j++)
	{
		temp_matrix.A[j] = A[j] - vector2.A[j];
	}

	return (temp_matrix);
}
//! operator overloaded
/*! Computes the inner product of two vectors < Vector1 Vector2>*/
/*! @param vector2 vector to be multiplied with*/
/*! @return the value of the inner product.*/
template <class T> T Vector<T>::operator * (Vector & vector2){
	T sum = 0;
	for(int i = 0; i < elements; i++)
	{
		sum = sum + A[i]*vector2.A[i];
	}

	return (sum);
}
//! operator overloaded
/*! Computes the product of an integer with the vector*/
/*! @param alpha the float value to be multiplied with*/
/*! @return the new vector formed.*/
template <class T> Vector<T> Vector<T>::operator *(float alpha){
	Vector<T> temp_matrix(elements);
	for(int i = 0; i < elements;i++){
		temp_matrix.A[i] = A[i]*alpha;
	}
	return temp_matrix;
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
	//	Vector<T> temp_vector;
	//	temp_vector.set_size(m);
	////	cout << "Element size of earlier vector " << elements << endl;
	////	cout << "Element size of new vector " << m << endl;
	//	for(int i = 0; i < elements; i++){
	//		temp_vector.A[i] = A[i];
	//	}
	//	A = temp_vector.A;
	//	elements = m;
	//	Vector<T> temp_vector;
	//	temp_vector.set_size(m);
	T *temp_vector;
	temp_vector = new T[m];
	//	cout << "Element size of earlier vector " << elements << endl;
	//	cout << "Element size of new vector " << m << endl;
	int n;
	if (elements < m){
		n = elements;
	}
	else{
		n = m;
	}
	for(int i = 0; i < n; i++){
		temp_vector[i] = A[i];
	}
	delete A;
	A = temp_vector;
	elements = m;
}

template <class T> void Vector<T>::set_size(int m){
	elements = m;
	A = new T[elements];
}

template <class T> int Vector<T>::get_size(){
	return elements;
}

//! [] opearator overloaded
/*! return the value of A[i]*/
template <class T> T & Vector<T>::operator [](int i){
	//	cout << "Value Stored";
	return (A[i]);
}

//! Creates the copy of of the vector
/*! @param vector2 Vector which is to be copied */
template <class T> void Vector<T>::copy_values(Vector & vector2){
	//	Vector<T> copy_vector(elements);
	for(int i = 0; i < vector2.get_size();i++){
		A[i] = vector2[i];
	}
	//	return copy_vector;
}
//! Deletes the vector
template<class T> void Vector<T>::del(){
	delete A;

}

//! Perform the addition operation of the form A = vector1 + alpha* Vector2
/*! @param vector1 vector */
/*! @param vector2 vector */
/*! @param alpha constant*/
template<class T> void Vector<T>::add(Vector & vector1, Vector & vector2, T alpha){
	for(int i = 0; i < vector1.get_size(); i++){
		A[i] = vector1[i] + alpha*vector2[i];
	}
}
//! Perform the substraction operation of the form A = vector1 - Vector2
/*! @param vector1 vector */
/*! @param vector2 vector */
template<class T> void Vector<T>::sub(Vector & vector1, Vector & vector2){
	for(int i = 0; i < vector1.get_size();i++){
		A[i] = vector1[i] - vector2[i];
	}
}

//! Perform the addition operation of the form A = vector1 - Vector2
/*! @param vector1 vector */
/*! @param vector2 vector */

template<class T> void Vector<T>::add(Vector & vector1,Vector & vector2){
	for(int i = 0; i < vector1.get_size();i++){
		A[i] = vector1[i] + vector2[i];
	}
}
//! set the value at a a particular location
/*! @param i the location where the value is to be inserted */
/*! @param value value which is to be stored at that location*/
template<class T> void Vector<T>::set_value(int i, T value){
	A[i] = value;
	cout << "Value Stored";
}
//! Perform the pairwise multiplication operation of the form A = vector1.* Vector2
/*! @param vector1 vector */
/*! @param vector2 vector */
template <class T> void Vector<T>::multiply_dot(Vector & vector1, Vector & vector2){
	for(int i = 0; i < vector1.get_size(); i++){
		A[i] = vector1[i] * vector2[i];
	}
}

template <class T> void Vector<T>::ones(){
	for(int i = 0; i < elements; i++){
		A[i] = 1;

	}
}
#endif /* Vector_H_ */
