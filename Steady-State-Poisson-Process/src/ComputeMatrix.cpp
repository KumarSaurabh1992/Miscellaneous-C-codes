/*
 * ComputeMatrix.cpp
 *
 *  Created on: Jan 30, 2015
 *      Author: saurabh
 */

#include "ComputeMatrix.h"
#include <fstream>
#include <math.h>
#include <time.h>
#define f_rhs(x,y) sin(3.14*x/2)*cos(3.14*y/2)

//! @return number of x - divisions
int ComputeMatrix::get_number_of_division_x(){
	return number_of_divisions_x;
}

//! @return number of y - divisions
int ComputeMatrix::get_number_of_division_y(){
	return number_of_divisions_y;
}

//! this sets the number of x - divisions and x-spacing
/*! @param N number of X - divisions*/
void ComputeMatrix::set_number_of_division_x(int N){
	h = 1.0/(N);
	number_of_divisions_x = N + 1;
}

//! This sets the number of y - divisions and y-spacing
/*! @param N number of y - divisions*/
void ComputeMatrix::set_number_of_division_y(int N){
	k = 1.0/(N);
	number_of_divisions_y = N + 1;
	//	cout <<"division y";
}

//! This takes the nput about the boundary condition
/*! Boundary condition is given in form of alpha*u + beeta*u' = gama*/
/*! The user inputs the boundary condition in the following order: bottom, right, top, left*/
void ComputeMatrix::get_boundary_condition(){
	int N = 4;
	set_boundary_size(N);
	double coeff_alpha,coeff_beeta,coeff_gama;
	//	alpha.initialize();
	//	beeta.initialize();
	//	gama.initialize();
	for(int i = 0; i < N; i++){
		//		cout << "Start" << endl;
		//		cout << alpha.get_size() << beeta.get_size() << gama.get_size() << endl;
		cout << "Enter the value of alpha" << endl;
		cin >> coeff_alpha;
		alpha[i] = coeff_alpha;
		//		alpha.display();
		cout << "Enter the value of beeta" << endl;
		cin >> coeff_beeta;
		beeta[i] = coeff_beeta;
		cout << "Enter the value of gamma" << endl;
		cin >> coeff_gama;
		//		cout << "End" << endl;
		//		cout << alpha.get_size() << beeta.get_size() << gama.get_size() << endl;
		gama[i] = coeff_gama;
		//		cout << "Done";
	}

}
//! Allocates the space for the boundary vectors
/*! @param N number of boundaries for the domain*/
void ComputeMatrix::set_boundary_size(int N){
	alpha.set_size(N);
	beeta.set_size(N);
	gama.set_size(N);
}

//! This is used to compute the matrix A and vector B when the grid is uniform in both x and y coordinates
/*! Matrix A is stored in sparse form.*/
/*! Vector X is initialized to 0*/
void ComputeMatrix::compute_general(){
	//	cout <<"Above";
	get_boundary_condition();
	//	cout << "In compute";
	int x_div,y_div;
	cout << "Enter the number of x divisons" << endl;
	cin >> x_div;
	cout << "Enter the number of y divisons" << endl;
	cin >> y_div;
	set_number_of_division_x(x_div);
	set_number_of_division_y(y_div);
	double temp_center, temp_left, temp_right, temp_bottom, temp_top;
	X.set_size((number_of_divisions_x )*(number_of_divisions_y ));
	X.initialize();
	B.set_size((number_of_divisions_x )*(number_of_divisions_y));
	spm.initialize((number_of_divisions_x)*(number_of_divisions_y));

	//	cout << "Line 74";
	for(int i = 0; i < number_of_divisions_y; i++){
		//		cout << i << endl;
		for(int j = 0; j < number_of_divisions_x; j++){
			double x = i*h;
			double y = j*k;
			double rhs = f_rhs(x,y);
			int row = (i)*(number_of_divisions_x) + (j);
			int col_left = (i)*(number_of_divisions_x) + (j - 1);
			int col_right = i*(number_of_divisions_x) + (j + 1);
			int col_top = (i + 1)*(number_of_divisions_x) + j;
			int col_bottom = (i - 1)*(number_of_divisions_x) + j;
			int col_center = i*(number_of_divisions_x) + j;

			if ((j == 0) && (i == 0)){									// bottom left point
				if((fabs(beeta[0] - 0.0) < pow(10.0,-6)) || (fabs(beeta[3] - 0.0) < pow(10.0,-6))){
					if (fabs(beeta[0] - 0.0) < pow(10.0,-6)){
						temp_center = alpha[0];
						spm.update_matrix(temp_center,row, col_center);
						B[row] = gama[0];
					}
					else{
						temp_center = alpha[3];
						spm.update_matrix(temp_center,row, col_center);
						B[row] = gama[3];
					}
				}
				else{
					temp_center = -(((2.0/(h*h))*(1 - (alpha[3]*h/beeta[3]))) + ((2.0/(k*k))*(1 - (alpha[0]*k/beeta[0]))));
					temp_right = 2.0/(h*h);
					temp_top = 2.0/(k*k);
					spm.update_matrix(temp_center,row, col_center);
					spm.update_matrix(temp_right,row,col_right);
					spm.update_matrix(temp_top,row,col_top);
					B[row] = rhs + 2.0*gama[3]/(beeta[3]*h) + (2.0*gama[0]/(beeta[0]*k));
				}

			}

			else if ((i == number_of_divisions_y - 1) && (j == 0)){			// top left point
				if((fabs(beeta[2] - 0.0) < pow(10.0,-6)) || (fabs(beeta[3] - 0.0) < pow(10.0,-6))){
					if (fabs(beeta[2] - 0.0) < pow(10.0,-6)){
						temp_center = alpha[2];
						spm.update_matrix(temp_center,row, col_center);
						B[row] = gama[2];
					}
					else{
						temp_center = alpha[3];
						spm.update_matrix(temp_center,row, col_center);
						B[row] = gama[3];
					}
				}
				else{
					temp_center = -(((2.0/(h*h))*(1 - (alpha[3]*h/beeta[3]))) + ((2.0/(k*k))*(1 + (alpha[2]*k/beeta[2]))));
					temp_right = 2.0/(h*h);
					temp_bottom = 2.0/(k*k);
					spm.update_matrix(temp_bottom,row,col_bottom);
					spm.update_matrix(temp_center,row, col_center);
					spm.update_matrix(temp_right,row,col_right);
					B[row] = rhs + 2.0*gama[3]/(beeta[3]*h) - (2.0*gama[2]/(beeta[2]*k));

				}
			}
			else if ((i == 0) && (j == number_of_divisions_x - 1)){			// bottom right point
				if((fabs(beeta[0] - 0.0) < pow(10.0,-6)) || (fabs(beeta[1] - 0.0) < pow(10.0,-6))){
					if (fabs(beeta[0] - 0.0) < pow(10.0,-6)){
						temp_center = alpha[0];
						spm.update_matrix(temp_center,row, col_center);
						B[row] = gama[0];
					}
					else{
						temp_center = alpha[1];
						spm.update_matrix(temp_center,row, col_center);
						B[row] = gama[1];
					}
				}
				else{
					temp_center = -(((2.0/(h*h))*(1 + (alpha[1]*h/beeta[1]))) + ((2.0/(k*k))*(1 - (alpha[0]*k/beeta[0]))));
					temp_left = 2.0/(h*h);
					temp_top = 2.0/(k*k);
					spm.update_matrix(temp_left,row,col_left);
					spm.update_matrix(temp_center,row, col_center);
					spm.update_matrix(temp_top,row,col_top);
					B[row] = rhs - 2.0*gama[1]/(beeta[1]*h) + (2.0*gama[0]/(beeta[0]*k));

				}
			}
			else if ((i == number_of_divisions_y - 1) && (j == number_of_divisions_x - 1)){		// top right point
				if((fabs(beeta[2] - 0.0) < pow(10.0,-6)) || (fabs(beeta[1] - 0.0) < pow(10.0,-6))){
					if (fabs(beeta[2] - 0.0) < pow(10.0,-6)){
						temp_center = alpha[2];
						spm.update_matrix(temp_center,row, col_center);
						B[row] = gama[2];
					}
					else{
						temp_center = alpha[1];
						spm.update_matrix(temp_center,row, col_center);
						B[row] = gama[1];
					}
				}
				else{
					temp_center = -(((2.0/(h*h))*(1 + (alpha[1]*h/beeta[1]))) + ((2.0/(k*k))*(1 + (alpha[2]*k/beeta[2]))));
					temp_left = 2.0/(h*h);
					temp_bottom = 2.0/(k*k);
					spm.update_matrix(temp_bottom,row,col_bottom);
					spm.update_matrix(temp_left,row,col_left);
					spm.update_matrix(temp_center,row, col_center);
					B[row] = rhs - 2.0*gama[1]/(beeta[1]*h) - (2.0*gama[2]/(beeta[2]*k));

				}
			}
			else if ((i == 0)){												// bottom face
				if((fabs(beeta[0] - 0.0) < pow(10.0,-6))){
					temp_center = alpha[0];
					spm.update_matrix(temp_center,row, col_center);
					B[row] = gama[0];
				}
				else{
					temp_center = -((2.0/(h*h)) + ((2.0/(k*k))*(1 - (alpha[0]*k/beeta[0]))));
					temp_left = 1.0/(h*h);
					temp_top = 2.0/(k*k);
					temp_right = 1.0/(h*h);
					spm.update_matrix(temp_left,row,col_left);
					spm.update_matrix(temp_center,row, col_center);
					spm.update_matrix(temp_right,row,col_right);
					spm.update_matrix(temp_top,row,col_top);
					B[row] = rhs + (2.0*gama[0]/(beeta[0]*k));

				}
			}
			else if (i == number_of_divisions_y - 1){							// top face
				if((fabs(beeta[2] - 0.0) < pow(10.0,-6))){
					temp_center = alpha[2];
					spm.update_matrix(temp_center,row, col_center);
					B[row] = gama[2];
				}
				else{
					temp_center = -((2.0/(h*h)) + ((2.0/(k*k))*(1 + (alpha[2]*k/beeta[2]))));
					temp_left = 1.0/(h*h);
					temp_bottom = 2.0/(k*k);
					temp_right = 1.0/(h*h);
					spm.update_matrix(temp_bottom,row,col_bottom);
					spm.update_matrix(temp_left,row,col_left);
					spm.update_matrix(temp_center,row, col_center);
					spm.update_matrix(temp_right,row,col_right);
					B[row] = rhs - (2.0*gama[2]/(beeta[2]*k));
				}
			}
			else if (j == number_of_divisions_x - 1){							// right face
				if((fabs(beeta[1] - 0.0) < pow(10.0,-6))){
					temp_center = alpha[1];
					spm.update_matrix(temp_center,row, col_center);
					B[row] = gama[1];
				}
				else{
					temp_center = -(((2.0/(h*h))*(1 + (alpha[1]*h/beeta[1]))) + ((2.0/(k*k))));
					temp_left = 2.0/(h*h);
					temp_bottom = 1.0/(k*k);
					temp_top = 1.0/(k*k);
					spm.update_matrix(temp_bottom,row,col_bottom);
					spm.update_matrix(temp_left,row,col_left);
					spm.update_matrix(temp_center,row, col_center);
					spm.update_matrix(temp_top,row,col_top);
					B[row] = rhs - 2.0*gama[1]/(beeta[1]*h);
				}
			}
			else if (j == 0){													// left face
				if((fabs(beeta[3] - 0.0) < pow(10.0,-6))){
					temp_center = alpha[3];
					spm.update_matrix(temp_center,row, col_center);
					B[row] = gama[3];

				}
				else{
					temp_center = -(((2.0/(h*h))*(1 - (alpha[3]*h/beeta[3]))) + ((2.0/(k*k))));
					temp_right = 2.0/(h*h);
					temp_top = 1.0/(k*k);
					temp_bottom = 1.0/(k*k);
					spm.update_matrix(temp_bottom,row,col_bottom);
					spm.update_matrix(temp_center,row, col_center);
					spm.update_matrix(temp_right,row,col_right);
					spm.update_matrix(temp_top,row,col_top);
					B[row] = rhs +(2.0*gama[3]/(beeta[3]*h));
				}

			}
			else{
				temp_center = -2.0*((1.0/(h*h)) + (1.0/(k*k)));					// center face
				temp_bottom = 1.0/(k*k);
				temp_right = 1.0/(h*h);
				temp_top = 1.0/(k*k);
				temp_left = 1.0/(h*h);
				spm.update_matrix(temp_bottom,row,col_bottom);
				spm.update_matrix(temp_left,row,col_left);
				spm.update_matrix(temp_center,row,col_center);
				spm.update_matrix(temp_right,row,col_right);
				spm.update_matrix(temp_top,row,col_top);

				B[row] = rhs;
			}

		}

	}

	spm.resize_matrix();
	ofstream fout("size_mat.txt");

		fout << number_of_divisions_x << endl;
		fout << number_of_divisions_y << endl;
		fout.close();
		cout << "File Written for size" << endl;
	cout << "Matrix formed \n";
	//	spm.display();
	//	cout << "*******" << endl;
	solve_iterative();
	//		B.display();
}

//! It creates the vector containing the information about spacing in the x direction
void ComputeMatrix::compute_h(){

	cout << "Enter the number of spacing in the x direction" << endl;
	cin >> number_of_x;
	x_spacing = new double*[number_of_x];
	for(int i = 0; i < number_of_x;i++){
		x_spacing[i] = new double[5];
	}
	double temp;
	for(int i = 0; i < number_of_x; i++){

		cout << "Enter the starting coordinate point" << endl;
		cin >> temp;
		x_spacing[i][0] = temp;
		cout << "Enter the end coordinate point" << endl;
		cin >> temp;
		x_spacing[i][1] = temp;
		cout << "Enter the value for h" << endl;
		cin >> temp;
		x_spacing[i][2] = temp;
		temp = (fabs(x_spacing[i][0] - x_spacing[i][1]))/(x_spacing[i][2]);
		//		cout << round(temp);
		//		cout << temp << endl;;
		//		cout << (fabs(temp - round(temp)));
		if ((fabs(temp - round(temp)) < pow(10.0,-6))) {
			x_spacing[i][3] = round(temp);
			x_spacing[i][4] = x_spacing[i][2];
			//			cout << "Entered";
		}
		else{
			x_spacing[i][3] = ceil(temp);
			x_spacing[i][4] = x_spacing[i][1] - (x_spacing[i][0]+ floor(temp)*x_spacing[i][2]);
		}
	}
	int m = 0;
	for (int i = 0; i < number_of_x ;i++){

		m += x_spacing[i][3];
		x_spacing[i][3] = m;
	}
	x_spacing[number_of_x - 1][3] +=1;
	//


}

//! It creates the vector containing information about spacing in the y - direction
void ComputeMatrix::compute_k(){
	cout << "Enter the number of spacing in the y direction" << endl;
	cin >> number_of_y;
	y_spacing = new double*[number_of_y];
	for(int i = 0; i < number_of_y;i++){
		y_spacing[i] = new double[5];
	}
	double temp;
	for(int i = 0; i < number_of_y; i++){

		cout << "Enter the starting coordinate point" << endl;
		cin >> temp;
		y_spacing[i][0] = temp;
		cout << "Enter the end coordinate point" << endl;
		cin >> temp;
		y_spacing[i][1] = temp;
		cout << "Enter the value for k" << endl;
		cin >> temp;
		y_spacing[i][2] = temp;
		temp = (fabs(y_spacing[i][0] - y_spacing[i][1]))/(y_spacing[i][2]);
		//		cout << round(temp);
		//		cout << temp << endl;;
		//		cout << (fabs(temp - round(temp)));
		if ((fabs(temp - round(temp)) < pow(10.0,-6))) {
			y_spacing[i][3] = round(temp);
			y_spacing[i][4] = y_spacing[i][2];
			//			cout << "Entered";
		}
		else{
			y_spacing[i][3] = ceil(temp);
			y_spacing[i][4] = y_spacing[i][1] - (y_spacing[i][0]+ floor(temp)*y_spacing[i][2]);
		}
	}
	int m = 0;
	for (int i = 0; i < number_of_y ;i++){

		m += y_spacing[i][3];
		y_spacing[i][3] = m;
	}
	y_spacing[number_of_y - 1][3] +=1;
	//

}

//! At a particular point, it returns the spacing in the left direction
/*! @param x_division the point of our interest*/
/*! @return the left x-spacing of that point*/
double ComputeMatrix::get_h_before(int x_division){
	if (x_division == number_of_divisions_x - 1){
		return x_spacing[number_of_x - 1][4];
	}
	for(int i = 0; i < number_of_x;i++){
		if(x_division == x_spacing[i][3]){
			return x_spacing[i][4];
		}
		else if (x_division < x_spacing[i][3]){
			return x_spacing[i][2];
		}
	}
	return 0.0;
}
//! At a particular point, it returns the spacing in the right direction
/*! @param x_division the point of our interest*/
/*! @return the right x-spacing of that point*/
double ComputeMatrix::get_h_after(int x_division){

	if (x_division == number_of_divisions_x - 2){
		return x_spacing[number_of_x - 1][4];
	}
	for(int i = 0; i < number_of_x;i++){
		if(x_division == x_spacing[i][3] - 1){
			return x_spacing[i][4];
		}
		else if (x_division < x_spacing[i][3]){
			return x_spacing[i][2];
		}
	}
	return 0.0;
}
//! At a particular point, it returns the spacing in the top direction
/*! @param y_division the point of our interest*/
/*! @return the top y-spacing of that point*/
double ComputeMatrix::get_k_after(int y_division){

	if (y_division == number_of_divisions_y - 2){
		return y_spacing[number_of_y - 1][4];
	}
	for(int i = 0; i < number_of_y;i++){
		if(y_division == y_spacing[i][3] - 1){
			return y_spacing[i][4];
		}
		else if (y_division < y_spacing[i][3]){
			return y_spacing[i][2];
		}
	}
	return 0.0;
}
//! At a particular point, it returns the spacing in the bottom direction
/*! @param y_division the point of our interest*/
/*! @return the bottom y-spacing of that point*/
double ComputeMatrix::get_k_before(int y_division){
	if (y_division == number_of_divisions_y - 1){
		return y_spacing[number_of_y - 1][4];
	}
	for(int i = 0; i < number_of_y;i++){
		if(y_division == y_spacing[i][3]){
			return y_spacing[i][4];
		}
		else if (y_division < y_spacing[i][3]){
			return y_spacing[i][2];
		}
	}
	return 0.0;
}

//! This is used to compute the matrix A and vector B when the grid is non - uniform in both x and y coordinates
/*! Matrix A is stored in sparse form.*/
/*! Vector X is initialized to 0*/
void ComputeMatrix::compute(){
	compute_h();
	compute_k();
	//	for(int i = 0; i < number_of_x; i++){
	//		for(int j = 0; j < 5; j++){
	//			cout << x_spacing[i][j] << "\t";
	//		}
	//		cout << endl;
	//	}
	//	for(int i = 0; i < number_of_y; i++){
	//			for(int j = 0; j < 5; j++){
	//				cout << y_spacing[i][j] << "\t";
	//			}
	//			cout << endl;
	//		}

	number_of_divisions_x = x_spacing[number_of_x - 1][3];
	number_of_divisions_y = y_spacing[number_of_y - 1][3];
	cout << "*************" <<endl;
	//	cout << number_of_divisions_x << endl;;
	//	cout << number_of_divisions_y;
	//	cout <<"Above";
	cout << "Enter the boundary conditions" << endl;
	cout << "Boundary condition is of the form: alpha*u + beeta * u' = gama" << endl;
	cout << "Enter the boundary condition in order of bottom, right, top, left" << endl;
	get_boundary_condition();
	//
	//	//	cout << "In compute";
	clock_t t;
	t = clock();
	double temp_center, temp_left, temp_right, temp_bottom, temp_top,h_before,h_after,k_before,k_after;
	X.set_size((number_of_divisions_x )*(number_of_divisions_y ));
	X.initialize();
	B.set_size((number_of_divisions_x )*(number_of_divisions_y));
	spm.initialize((number_of_divisions_x)*(number_of_divisions_y));
	float rhs = -2;
	//		cout << "Line 74";
	for(int i = 0; i < number_of_divisions_y; i++){
		//		cout << i << endl;

		for(int j = 0; j < number_of_divisions_x; j++){

			int row = (i)*(number_of_divisions_x) + (j);
			int col_left = (i)*(number_of_divisions_x) + (j - 1);
			int col_right = i*(number_of_divisions_x) + (j + 1);
			int col_top = (i + 1)*(number_of_divisions_x) + j;
			int col_bottom = (i - 1)*(number_of_divisions_x) + j;
			int col_center = i*(number_of_divisions_x) + j;
			//
			if ((j == 0) && (i == 0)){									// bottom left point
				if((fabs(beeta[0] - 0.0) < pow(10.0,-6)) || (fabs(beeta[3] - 0.0) < pow(10.0,-6))){
					if (fabs(beeta[0] - 0.0) < pow(10.0,-6)){
						temp_center = alpha[0];
						spm.update_matrix(temp_center,row, col_center);
						B[row] = gama[0];
					}
					else{
						temp_center = alpha[3];
						spm.update_matrix(temp_center,row, col_center);
						B[row] = gama[3];
					}
				}
				else{
					rhs =
					h_after = get_h_after(j);
					k_after = get_k_after(i);
					temp_center = -(((2.0/(h_after*h_after))*(1 - (alpha[3]*h_after/beeta[3]))) + ((2.0/(k_after*k_after))*(1 - (alpha[0]*k_after/beeta[0]))));
					temp_right = 2.0/(h_after*h_after);
					temp_top = 2.0/(k_after*k_after);
					spm.update_matrix(temp_center,row, col_center);
					spm.update_matrix(temp_right,row,col_right);
					spm.update_matrix(temp_top,row,col_top);
					B[row] = rhs + 2.0*gama[3]/(beeta[3]*h_after) + (2.0*gama[0]/(beeta[0]*k_after));
				}
				//
			}
			//
			else if ((i == number_of_divisions_y - 1) && (j == 0)){			// top left point
				if((fabs(beeta[2] - 0.0) < pow(10.0,-6)) || (fabs(beeta[3] - 0.0) < pow(10.0,-6))){
					if (fabs(beeta[2] - 0.0) < pow(10.0,-6)){
						temp_center = alpha[2];
						spm.update_matrix(temp_center,row, col_center);
						B[row] = gama[2];
					}
					else{
						temp_center = alpha[3];
						spm.update_matrix(temp_center,row, col_center);
						B[row] = gama[3];
					}
				}
				else{
					h_after = get_h_after(j);
					k_before = get_k_before(i);

					temp_center = -(((2.0/(h_after*h_after))*(1 - (alpha[3]*h_after/beeta[3]))) + ((2.0/(k_before*k_before))*(1 + (alpha[2]*k_before/beeta[2]))));
					temp_right = 2.0/(h_after*h_after);
					temp_bottom = 2.0/(k_before*k_before);
					spm.update_matrix(temp_bottom,row,col_bottom);
					spm.update_matrix(temp_center,row, col_center);
					spm.update_matrix(temp_right,row,col_right);
					B[row] = rhs + 2.0*gama[3]/(beeta[3]*h_after) - (2.0*gama[2]/(beeta[2]*k_before));
					//
				}
			}
			else if ((i == 0) && (j == number_of_divisions_x - 1)){			// bottom right point
				if((fabs(beeta[0] - 0.0) < pow(10.0,-6)) || (fabs(beeta[1] - 0.0) < pow(10.0,-6))){
					if (fabs(beeta[0] - 0.0) < pow(10.0,-6)){
						temp_center = alpha[0];
						spm.update_matrix(temp_center,row, col_center);
						B[row] = gama[0];
					}
					else{
						temp_center = alpha[1];
						spm.update_matrix(temp_center,row, col_center);
						B[row] = gama[1];
					}
				}
				else{

					h_before = get_h_before(j);
					k_after = get_k_after(i);

					temp_center = -(((2.0/(h_before*h_before))*(1 + (alpha[1]*h_before/beeta[1]))) + ((2.0/(k_after*k_after))*(1 - (alpha[0]*k_after/beeta[0]))));
					temp_left = 2.0/(h_before*h_before);
					temp_top = 2.0/(k_after*k_after);
					spm.update_matrix(temp_left,row,col_left);
					spm.update_matrix(temp_center,row, col_center);
					spm.update_matrix(temp_top,row,col_top);
					B[row] = rhs - 2.0*gama[1]/(beeta[1]*h_before) + (2.0*gama[0]/(beeta[0]*k_after));
					//
				}
			}
			else if ((i == number_of_divisions_y - 1) && (j == number_of_divisions_x - 1)){		// top right point
				if((fabs(beeta[2] - 0.0) < pow(10.0,-6)) || (fabs(beeta[1] - 0.0) < pow(10.0,-6))){
					if (fabs(beeta[2] - 0.0) < pow(10.0,-6)){
						temp_center = alpha[2];
						spm.update_matrix(temp_center,row, col_center);
						B[row] = gama[2];
					}
					else{
						temp_center = alpha[1];
						spm.update_matrix(temp_center,row, col_center);
						B[row] = gama[1];
					}
				}
				else{
					h_before = get_h_before(j);
					k_before = get_k_before(i);
					temp_center = -(((2.0/(h_before*h_before))*(1 + (alpha[1]*h_before/beeta[1]))) + ((2.0/(k_before*k_before))*(1 + (alpha[2]*k_before/beeta[2]))));
					temp_left = 2.0/(h_before*h_before);
					temp_bottom = 2.0/(k_before*k_before);
					spm.update_matrix(temp_bottom,row,col_bottom);
					spm.update_matrix(temp_left,row,col_left);
					spm.update_matrix(temp_center,row, col_center);
					B[row] = rhs - 2.0*gama[1]/(beeta[1]*h_before) - (2.0*gama[2]/(beeta[2]*k_before));

				}
			}
			else if ((i == 0)){												// bottom face
				if((fabs(beeta[0] - 0.0) < pow(10.0,-6))){
					temp_center = alpha[0];
					spm.update_matrix(temp_center,row, col_center);
					B[row] = gama[0];
				}
				else{
					h_before = get_h_before(j);
					h_after = get_h_after(j);
					k_after = get_k_after(i);
					temp_center = -((2.0/(h_after*h_before)) + ((2.0/(k_after*k_after))*(1 - (alpha[0]*k_after/beeta[0]))));
					temp_left = 2.0/(h_before*(h_before + h_after));
					temp_top = 2.0/(k_after*k_after);
					temp_right = 2.0/(h_after*(h_before + h_after));
					spm.update_matrix(temp_left,row,col_left);
					spm.update_matrix(temp_center,row, col_center);
					spm.update_matrix(temp_right,row,col_right);
					spm.update_matrix(temp_top,row,col_top);
					B[row] = rhs + (2.0*gama[0]/(beeta[0]*k_after));
					//
				}
			}
			else if (i == number_of_divisions_y - 1){							// top face
				if((fabs(beeta[2] - 0.0) < pow(10.0,-6))){
					temp_center = alpha[2];
					spm.update_matrix(temp_center,row, col_center);
					B[row] = gama[2];
				}
				else{
					k_before = get_k_before(i);
					h_after = get_h_after(j);
					h_before = get_h_before(j);
					temp_center = -((2.0/(h_before*h_after)) + ((2.0/(k_before*k_before))*(1 + (alpha[2]*k_before/beeta[2]))));
					temp_left = 2.0/(h_before*(h_after + h_before));
					temp_bottom = 2.0/(k_after*k_after);
					temp_right = 2.0/(h_after*(h_after + h_before));
					spm.update_matrix(temp_bottom,row,col_bottom);
					spm.update_matrix(temp_left,row,col_left);
					spm.update_matrix(temp_center,row, col_center);
					spm.update_matrix(temp_right,row,col_right);
					B[row] = rhs - (2.0*gama[2]/(beeta[2]*k_before));
				}
			}
			else if (j == number_of_divisions_x - 1){							// right face
				if((fabs(beeta[1] - 0.0) < pow(10.0,-6))){
					temp_center = alpha[1];
					spm.update_matrix(temp_center,row, col_center);
					B[row] = gama[1];
				}
				else{
					k_before = get_k_before(i);
					k_after = get_k_after(i);
					h_before = get_h_before(j);
					temp_center = -(((2.0/(h_before*h_before))*(1 + (alpha[1]*h_before/beeta[1]))) + ((2.0/(k_after*k_before))));
					temp_left = 2.0/(h_before*h_before);
					temp_bottom = 2.0/(k_before*(k_before + k_after));
					temp_top = 2.0/(k_after*(k_before + k_after));
					spm.update_matrix(temp_bottom,row,col_bottom);
					spm.update_matrix(temp_left,row,col_left);
					spm.update_matrix(temp_center,row, col_center);
					spm.update_matrix(temp_top,row,col_top);
					B[row] = rhs - 2.0*gama[1]/(beeta[1]*h_before);
				}
			}
			else if (j == 0){													// left face
				if((fabs(beeta[3] - 0.0) < pow(10.0,-6))){
					temp_center = alpha[3];
					spm.update_matrix(temp_center,row, col_center);
					B[row] = gama[3];

				}
				else{
					h_after = get_h_after(j);
					k_before = get_k_before(i);
					k_after = get_k_after(i);
					temp_center = -(((2.0/(h_after*h_after))*(1 - (alpha[3]*h_after/beeta[3]))) + ((2.0/(k_after*k_before))));
					temp_right = 2.0/(h_after*h_after);
					temp_top = 2.0/(k_after*(k_before + k_after));
					temp_bottom = 2.0/(k_before*(k_after + k_before));
					spm.update_matrix(temp_bottom,row,col_bottom);
					spm.update_matrix(temp_center,row, col_center);
					spm.update_matrix(temp_right,row,col_right);
					spm.update_matrix(temp_top,row,col_top);
					B[row] = rhs +(2.0*gama[3]/(beeta[3]*h_after));
				}

			}
			else{																					// center face
				h_after = get_h_after(j);
				h_before = get_h_before(j);
				k_after = get_k_after(i);
				k_before = get_k_before(i);
				temp_center = -2.0*((1.0/(h_after*h_before)) + (1.0/(k_after*k_before)));
				temp_bottom = 2.0/(k_before*(k_before + k_after));
				temp_right = 2.0/(h_after*(h_before + h_after));
				temp_top = 2.0/(k_after*(k_after + k_before));
				temp_left = 2.0/(h_before*(h_after + h_before));
				spm.update_matrix(temp_bottom,row,col_bottom);
				spm.update_matrix(temp_left,row,col_left);
				spm.update_matrix(temp_center,row,col_center);
				spm.update_matrix(temp_right,row,col_right);
				spm.update_matrix(temp_top,row,col_top);

				B[row] = rhs;
			}

		}

	}

	spm.resize_matrix();
	//	spm.display();
	cout <<"*******" << endl;
	cout << "Matrix formed \n";
	t = clock() - t;
	cout << "Time taken in formation of matrix is " << ((float)t)/CLOCKS_PER_SEC << "seconds" << endl;
	ofstream fout("size_mat.txt");

	fout << number_of_divisions_x << endl;
	fout << number_of_divisions_y << endl;
	fout.close();
	cout << "File Written for size" << endl;
	//		B.display();

	//	int number_of_x;
	//
	solve_iterative();

	//	float temp_center, temp_left, temp_right, temp_bottom, temp_top;
	//	X.set_size((number_of_divisions_x )*(number_of_divisions_y ));
	//	X.initialize();
	//	B.set_size((number_of_divisions_x )*(number_of_divisions_y));
	//	spm.initialize((number_of_divisions_x)*(number_of_divisions_y));
	//	for(int i = 0; i < number_of_divisions_y; i++){
	//		for(int j = 0; j < number_of_divisions_x; j++){
	//			int row = (i)*(number_of_divisions_x) + (j);
	//			int col_left = (i)*(number_of_divisions_x) + (j - 1);
	//			int col_right = i*(number_of_divisions_x) + (j + 1);
	//			int col_top = (i + 1)*(number_of_divisions_x) + j;
	//			int col_bottom = (i - 1)*(number_of_divisions_x) + j;
	//			int col_center = i*(number_of_divisions_x) + j;
	//			if ((j == 0) && (i == 0)){									// bottom left point
	//				temp_center = -2.0*((1.0/(h*h)) + (1.0/(k*k)));
	//				temp_right = 1.0/(h*h);
	//				temp_top = 1.0/(k*k);
	//
	//				spm.update_matrix(temp_center,row, col_center);
	//				spm.update_matrix(temp_right,row,col_right);
	//				spm.update_matrix(temp_top,row,col_top);
	//			}
	//			else if ((i == number_of_divisions_y - 1) && (j == 0)){			// top left point
	//				temp_center = -2.0*((1.0/(h*h)) + (1.0/(k*k)));
	//				temp_bottom = 1.0/(k*k);
	//				temp_right = 1.0/(h*h);
	//
	//				spm.update_matrix(temp_center,row,col_center);
	//				spm.update_matrix(temp_bottom,row,col_bottom);
	//				spm.update_matrix(temp_right,row, col_right);
	//			}
	//			else if ((i == 0) && (j == number_of_divisions_x - 1)){			// bottom right point
	//				temp_center = -2.0*((1.0/(h*h)) + (1.0/(k*k)));
	//				temp_top = 1.0/(k*k);
	//				temp_left = 1.0/(h*h);
	//
	//				spm.update_matrix(temp_center,row,col_center);
	//				spm.update_matrix(temp_top,row,col_top);
	//				spm.update_matrix(temp_left,row,col_left);
	//			}
	//			else if ((i == number_of_divisions_y - 1) && (j == number_of_divisions_x - 1)){		// top right point
	//				temp_center = -2.0*((1.0/(h*h)) + (1.0/(k*k)));
	//				temp_bottom = 1.0/(k*k);
	//				temp_left = 1.0/(h*h);
	//
	//				spm.update_matrix(temp_center,row,col_center);
	//				spm.update_matrix(temp_bottom,row,col_bottom);
	//				spm.update_matrix(temp_left,row,col_left);
	//			}
	//			else if ((i == 0)){												// bottom face
	//				temp_center = -2.0*((1.0/(h*h)) + (1.0/(k*k)));
	//				temp_right = 1.0/(h*h);
	//				temp_top = 1.0/(k*k);
	//				temp_left = 1.0/(h*h);
	//
	//				spm.update_matrix(temp_center,row,col_center);
	//				spm.update_matrix(temp_right,row,col_right);
	//				spm.update_matrix(temp_top,row,col_top);
	//				spm.update_matrix(temp_left,row,col_left);
	//			}
	//			else if (i == number_of_divisions_y - 1){							// top face
	//				temp_center = -2.0*((1.0/(h*h)) + (1.0/(k*k)));
	//				temp_bottom = 1.0/(k*k);
	//				temp_right = 1.0/(h*h);
	//				temp_left = 1.0/(h*h);
	//
	//				spm.update_matrix(temp_center,row,col_center);
	//				spm.update_matrix(temp_bottom,row,col_bottom);
	//				spm.update_matrix(temp_right,row,col_right);
	//				spm.update_matrix(temp_left,row,col_left);
	//			}
	//			else if (j == number_of_divisions_x - 1){							// right face
	//				temp_center = -2.0*((1.0/(h*h)) + (1.0/(k*k)));
	//				temp_bottom = 1.0/(k*k);
	//				temp_left = 1.0/(h*h);
	//				temp_top = 1.0/(k*k);
	//
	//				spm.update_matrix(temp_center,row,col_center);
	//				spm.update_matrix(temp_bottom,row,col_bottom);
	//				spm.update_matrix(temp_left,row,col_left);
	//				spm.update_matrix(temp_top,row,col_top);
	//			}
	//			else if (j == 0){													// left face
	//				temp_center = -2.0*((1.0/(h*h)) + (1.0/(k*k)));
	//				temp_bottom = 1.0/(k*k);
	//				temp_right = 1.0/(h*h);
	//				temp_top = 1.0/(k*k);
	//
	//				spm.update_matrix(temp_center,row,col_center);
	//				spm.update_matrix(temp_bottom,row,col_bottom);
	//				spm.update_matrix(temp_right,row,col_right);
	//				spm.update_matrix(temp_top,row,col_top);
	//			}
	//			else{
	//				temp_center = -2.0*((1.0/(h*h)) + (1.0/(k*k)));					// center face
	//				temp_bottom = 1.0/(k*k);
	//				temp_right = 1.0/(h*h);
	//				temp_top = 1.0/(k*k);
	//				temp_left = 1.0/(h*h);
	//
	//				spm.update_matrix(temp_center,row,col_center);
	//				spm.update_matrix(temp_bottom,row,col_bottom);
	//				spm.update_matrix(temp_right,row,col_right);
	//				spm.update_matrix(temp_top,row,col_top);
	//				spm.update_matrix(temp_left,row,col_left);
	//			}
	//			B[row] = -2.0;
	//		}
	//
	//	}
	//
	//	spm.resize_matrix();
}

//! Displays the sparse matrix
void ComputeMatrix:: compute_matrix_display(){
	spm.display();
}

//! Solve the equation AX = B
void ComputeMatrix::solve_iterative(){
	Iterative_Solver its;
	cout << "Enter the solver you want to use" << endl;
	cout << "1. Gauss Siedel with or without relaxation" << endl;
	cout << "2. BiConjugate Gradient without preconditioner" << endl;
	cout << "3. Biconjugate Gradient with preconditioner" << endl;
	cout << "4. Conjugate Gradient Method" << endl;
	int choice;
	cin >> choice;
	if(choice == 1){
		clock_t t;
		t = clock();
		its.Gauss_Siedel(spm,X,B);
		t = clock() - t;
		cout << "Time taken by Gauss Seidel is  " << ((float)t)/CLOCKS_PER_SEC << "seconds" << endl;
	}
	else if (choice == 2){
		its.BiCG(spm,X,B);


	}
	else if (choice == 3){
		int choice2;
		cout << "0. Jacobi Preconditioner" << endl;
		cout << "1. ILU Preconditioner" << endl;
		cout << "2. Gauss Seidel Preconditioner" <<endl;
		cin >> choice2;
		its.BiCG_preconditioner(spm,X,B,choice2);

	}
	else if(choice == 4){
		clock_t t;
		t = clock();
		its.CG(spm,X,B);
		t = clock() - t;
		cout << "Time taken by Conjugate Gradient is  " << ((float)t)/CLOCKS_PER_SEC << "seconds" << endl;
		cout << "Writing in file" << endl;
		ofstream fout("solver.txt");
		for(int i = 0; i < X.get_size(); i++){
			fout << X[i] << endl;
		}
		fout.close();
		cout << "File Written" << endl;
	}

	//	cout <<"Reached Iter";
	//	X.display();


}
