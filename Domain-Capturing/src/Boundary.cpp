/*
 * Boundary.cpp
 *
 *  Created on: Jan 25, 2015
 *      Author: saurabh
 */

#include "Boundary.h"
#include <iostream>
#include <fstream>
using namespace std;

void Boundary::set_size(int N){
	number_of_points = N;
	points = new Domain[N];
}

void Boundary::set_Boundary_Points(){
	for(int i = 0; i < number_of_points; i++){
			points[i].get_Point();
			points[i].set_compartment_number(i,i);
			points[i].set_end(i);
			points[i].set_curve(0);
			points[i].set_index(i);
		}

}

int Boundary::get_number_of_points(){
	return number_of_points;
}

void Boundary::display_points(){
	cout << "*****************************" << endl;
	cout << "Your list of points are" << endl;
	for(int i = 0; i < number_of_points; i++){
		cout << i << ": ";
		points[i].display();
		cout << endl;
	}
	cout << "****************************" << endl;
}

void Boundary::boundary_choices(){
	cout << "********************************************" << endl;
	cout << "Your choices for the curve you want to fit:" << endl;
	cout << "1. Linear" << endl;
	cout << "2. Circle" << endl;
	cout << "3. Ellipse" << endl;
	cout << "4. Quadratic" << endl;
	cout << "5. Exponential" << endl;
	cout << "6. Parbolic" << endl;
	cout << "******************************************" << endl;
}

void Boundary::display_boundary_points(int index1,int index2){
	cout << "Enter the curve you want to fit between " ;
	points[index1].display();
	cout << " and ";
	points[index2].display();
	cout << endl;
}

void Boundary::post_grid_opeartion(int index1,int index2, int choice){

	points[index1].set_end(index2);
	points[index1].set_curve(choice);
	set_number_of_compartments(index1,index2);
}

void Boundary::display_which_curve(){
	int first_point,second_point;
	cout << "Enter the first point index" << endl;
	cin >> first_point;
	cout << "Enter the second point index" << endl;
	cin >> second_point;
	int curve_index;
	bool met;
	met = false;
	if(points[first_point].get_end() == second_point){
		curve_index =  points[first_point].get_curve();
		met = true;
		}
		else if ((points[second_point].get_end() == first_point)){
			curve_index = points[second_point].get_curve();
			met = true;

			}
			else{
				cout << "No curve was drawn between " ;
				points[first_point].display();
				cout << " and ";
				points[second_point].display();
				cout << endl;
			}
			if (met == true){
				if (curve_index == 1){
					cout << "Line was drawn between " ;

				}
				else if (curve_index == 2){
					cout << "Circle was drawn between " ;
				}
				else if(curve_index == 3){
					cout << "Ellipse was drawn between " ;
				}
				else if(curve_index == 4){
					cout << "Quadratic curve was drawn between " ;
				}
				else if(curve_index == 5){
					cout << "Exponential curve was drawn between " ;
				}
				else if(curve_index == 6){
					cout << "Parabola was drawn between " ;
				}
				points[first_point].display();
				cout << " and ";
				points[second_point].display();
				cout << endl;
			}
}

int Boundary::get_compartment(int i){
	int compartment_number;
	Domain temp;
	temp = points[i];


	while (temp.get_compartment_number() != temp.get_index()){
		temp = points[temp.get_compartment_number()];

	}
	compartment_number = temp.get_compartment_number();
	return compartment_number;
}


void Boundary::set_number_of_compartments(int i, int j){
	cout << endl;
	if (get_compartment(i) != get_compartment(j)){
			number_of_compartments = number_of_compartments - 1;
		}
	points[i].set_compartment_number(get_compartment(i),get_compartment(j));
	points[j].set_compartment_number(get_compartment(i),get_compartment(j));
}

int Boundary::get_number_of_compartments(){
	return number_of_compartments;
}

void Boundary::set_number_of_initial_compartments(int N){
	number_of_compartments = N;
}

void Boundary::make_grid_choice(ofstream & fout){


	int choice;
	GridPoints gps;
	int number_of_points;
	int first_point;
	int second_point;
	cout << "Enter the first point index" << endl;
	cin >> first_point;
	cout << "Enter the second point index" << endl;
	cin >> second_point;
	boundary_choices();
	fout << points[first_point].get_x_coordinate() << '\t'<< points[first_point].get_y_coordinate() << endl;
	display_boundary_points(first_point,second_point);
	cout << "Enter your choice" << endl;
	cin >> choice;
	cout << "Enter the number of points" << endl;
	cin >> number_of_points;
	if (choice == 1){
		gps.Linear_Grid(points[first_point],points[second_point],number_of_points);
	}
	else if (choice == 2){
		gps.Circular_Grid(points[first_point],points[second_point],number_of_points);
	}
	else if (choice == 3){
		gps.Elliptic_Grid(points[first_point],points[second_point],number_of_points);
	}
	else if(choice == 4){
		gps.Quadratic_Grid(points[first_point],points[second_point],number_of_points);
	}
	else if(choice == 5){
		gps.Exponential_Grid(points[first_point],points[second_point],number_of_points);
	}
	else if(choice == 6){
		gps.Parabolic_Grid(points[first_point],points[second_point],number_of_points);
	}
	post_grid_opeartion(first_point,second_point,choice);
	for (int j = 0; j < number_of_points; j++){
		fout << gps.grid_points[j].get_x_coordinate() << '\t'<< gps.grid_points[j].get_y_coordinate() << endl;
	}
	fout << points[second_point].get_x_coordinate() << '\t'<< points[second_point].get_y_coordinate() << endl;
	delete gps.grid_points;

}
