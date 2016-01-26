/*
 * GridPoints.cpp
 *
 *  Created on: Jan 22, 2015
 *      Author: saurabh
 */

#include "GridPoints.h"
#include "Point.h"
#include <math.h>
#include <iostream>
using namespace std;

# define PI 3.14159265

void GridPoints::divide_domain_Line(Point point1, Point point2, int N){
	float x_coordinate_point1 = point1.get_x_coordinate();
	float y_coordinate_point1 = point1.get_y_coordinate();

	float x_coordinate_point2 = point2.get_x_coordinate();
	float y_coordinate_point2 = point2.get_y_coordinate();

	float step_length;
	grid_points = new Point[N];
	float x,y;
	if (fabs(x_coordinate_point1 - x_coordinate_point2) < pow(10.0,-6)){
		step_length = (y_coordinate_point2 - y_coordinate_point1)/(N + 1);
		y = y_coordinate_point1;
		x = x_coordinate_point1;
		for(int i = 0; i < N; i++){
			y = y+ step_length;
			grid_points[i].get_Coordinate(x,y);

		}

	}
	else{
		float slope = ((y_coordinate_point1 - y_coordinate_point2)*1.0)/(x_coordinate_point1 - x_coordinate_point2);
		float intercept = y_coordinate_point1 - (slope*x_coordinate_point1);
		step_length = (x_coordinate_point2 - x_coordinate_point1)/(N + 1);
		x = x_coordinate_point1;
		y = y_coordinate_point1;
		for(int i = 0; i < N; i++){

			x = x + step_length;
			y = slope*x + intercept;
			grid_points[i].get_Coordinate(x,y);

		}
	}


}

float GridPoints::getRadius(Point point1, Point center){
	float rad = sqrt(pow((point1.get_x_coordinate() - center.get_x_coordinate()),2) + pow((point1.get_y_coordinate() - center.get_y_coordinate()),2));
	return rad;
}

float GridPoints::getAngle(Point point1, Point point2){
//	if ((point1.get_x_coordinate() - point2.get_x_coordinate()) < 0){
//		if ((point1.get_y_coordinate() - point2.get_y_coordinate()) <= 0){
//			float angle = atan2(fabs(point1.get_y_coordinate() - point2.get_y_coordinate()), fabs(point1.get_x_coordinate() - point2.get_x_coordinate()));
//			return angle + PI;
//		}
//		else{
//			float angle = atan2((point1.get_y_coordinate() - point2.get_y_coordinate()), (point1.get_x_coordinate() - point2.get_x_coordinate()));
//			return angle + PI;
//		}
//
//		}
		float angle = atan2((point1.get_y_coordinate() - point2.get_y_coordinate()), (point1.get_x_coordinate() - point2.get_x_coordinate()));
		if (angle < 0){
				return (angle + 2*PI);
		}

		return angle;
}
void GridPoints::divide_domain_Circle(Point point1, Point point2,int N,bool direction){
	cout << "Enter coordinates for center" << endl;
	Point center;
	center.get_Point();
	float radius = getRadius(point1, center);
	float angle_start = getAngle(point1,center);
	float angle_end = getAngle(point2,center);
	float x,y;
	float thetha;
	grid_points = new Point[N];
	if (direction == 1){

		float step_angle = ((angle_end - angle_start)/(N + 1));
//		cout << step_angle <<endl;
		thetha = angle_start;
		for (int i = 0; i < N; i++){

			thetha = thetha + step_angle;
			x = center.get_x_coordinate() + radius*cos(thetha);
			y = center.get_y_coordinate() + radius*sin(thetha);
			grid_points[i].get_Coordinate(x,y);

		}

	}
	else{

		if (angle_start < angle_end){
					angle_start = angle_start + 2*PI;
		}
		else{
				angle_end = angle_end + 2*PI;
		}
		float step_angle = ((angle_end - angle_start)/(N + 1));

		thetha = angle_start;
		for (int i = 0; i < N; i++){

			thetha = thetha + step_angle;
			x = center.get_x_coordinate() + radius*cos(thetha);
			y = center.get_y_coordinate() + radius*sin(thetha);
			grid_points[i].get_Coordinate(x,y);

		}
	}
}

void GridPoints::divide_domain_Ellipse(Point point1,Point point2,int N,bool direction){
	cout << "Enter coordinates for center for ellipse" << endl;
	Point center;
	center.get_Point();

	float angle_start = getAngle(point1, center);
	float angle_end = getAngle(point2, center);

	float a,b;
	if ((((fabs(angle_start - PI)) < pow(10.0,-6)) || ((fabs(angle_start - 0.0)) < pow(10.0,-6))) && ((fabs(angle_end - PI) < pow(10.0,-6)) || (fabs(angle_end - 0.0) < pow(10.0,-6)))){
		cout << "Enter the value of b" << endl;
		cin >> b;
	}
	else if ((fabs(angle_start - PI) < pow(10.0,-6)) || (fabs(angle_start - 0.0) < pow(10.0,-6))){
			b = fabs((point2.get_y_coordinate() - center.get_y_coordinate())/sin(angle_end));
	}
	else{
		b = fabs((point1.get_y_coordinate() - center.get_y_coordinate())/sin(angle_start));
	}
	if ((((fabs(angle_start - PI/2.0)) < pow(10.0,-6)) || ((fabs(angle_start - 3*PI/2.0)) < pow(10.0,-6))) && ((fabs(angle_end - PI/2.0) < pow(10.0,-6)) || (fabs(angle_end - 3*PI/2.0) < pow(10.0,-6)))){

		cout << "Enter the value of a" << endl;
		cin >> a;

	}
	else if ((fabs(angle_start - PI/2.0) < pow(10.0,-6)) || (fabs(angle_start - 3*PI/2.0) < pow(10.0,-6))){
			a = fabs((point2.get_x_coordinate() - center.get_x_coordinate())/cos(angle_end));
	}
	else{
		a = fabs((point1.get_x_coordinate() - center.get_x_coordinate())/cos(angle_start));
	}
	float x,y;
	float thetha;
	grid_points = new Point[N];
//	cout << angle_start<< endl;;
//	cout << angle_end;
	if (direction == 1){
		float step_angle = ((angle_end - angle_start)/(N + 1));
//		cout << step_angle <<endl;
		thetha = angle_start;
		for (int i = 0; i < N; i++){

			thetha = thetha + step_angle;
			x = center.get_x_coordinate() + a*cos(thetha);
			y = center.get_y_coordinate() + b*sin(thetha);
			grid_points[i].get_Coordinate(x,y);

		}

	}
	else{
		if (angle_start < angle_end){
			angle_start = angle_start + 2*PI;
		}
		else{
			angle_end = angle_end + 2*PI;
		}


		float step_angle = ((angle_end - angle_start)/(N + 1));
			thetha = angle_start;
			for (int i = 0; i < N; i++){

				thetha = thetha + step_angle;
				x = center.get_x_coordinate() + a*cos(thetha);
				y = center.get_y_coordinate() + b*sin(thetha);
				grid_points[i].get_Coordinate(x,y);

			}
	}


}

void GridPoints::divide_domain_Parabola(Point point1,Point point2,int N){
	Point center;
	cout <<"Enter the center";
	center.get_Point();
	int choice;
	cout << "Select which type of parabola you want" << endl;
	cout <<"1. y^2 = 4ax" << endl;
	cout <<"2. x^2 = 4ay" << endl;
	cin >> choice;
	float step_length;
	float a,x,y;
	grid_points = new Point[N];
	if (choice == 1){
		if (point1.get_y_coordinate() == center.get_y_coordinate()){
			a = pow((point1.get_y_coordinate() - center.get_y_coordinate()),2)/(4*(point1.get_x_coordinate() - center.get_x_coordinate()));
		}
		else
		{
			a = pow((point2.get_y_coordinate() - center.get_y_coordinate()),2)/(4*(point2.get_x_coordinate() - center.get_x_coordinate()));
		}
		step_length = ((point2.get_y_coordinate() - point1.get_y_coordinate()))/(N + 1);
		y = point1.get_y_coordinate();
		for(int i = 0; i < N; i++){
			y = y + step_length;
			x = center.get_x_coordinate() + pow((y - center.get_y_coordinate()),2)/(4*a);
			grid_points[i].get_Coordinate(x,y);
		}
	}
	else
	{	if (point1.get_x_coordinate() == center.get_x_coordinate()){
		a = pow((point1.get_x_coordinate() - center.get_x_coordinate()),2)/(4*(point1.get_y_coordinate() - center.get_y_coordinate()));
	}
	else
	{
		a = pow((point2.get_x_coordinate() - center.get_x_coordinate()),2)/(4*(point2.get_y_coordinate() - center.get_y_coordinate()));
	}

		cout << a;
		step_length = ((point2.get_x_coordinate() - point1.get_x_coordinate()))/(N + 1);
		x = point1.get_x_coordinate();
		for(int i = 0; i < N; i++){
			x = x + step_length;
			y = center.get_y_coordinate() + pow(x - center.get_x_coordinate(),2)/(4*a);
			grid_points[i].get_Coordinate(x,y);
		}

	}
}

void GridPoints::divide_domain_exponential(Point point1, Point point2,int N){
	float a = log(point1.get_y_coordinate()/point2.get_y_coordinate())/(point1.get_x_coordinate() - point2.get_x_coordinate());
	float k = point1.get_y_coordinate()/exp(a*point1.get_x_coordinate());
	float step_length = (point2.get_x_coordinate() - point1.get_x_coordinate())/(N + 1);
	float x = point1.get_x_coordinate();
	grid_points= new Point[N];
	float y;
	for(int i = 0; i < N; i++){
		x = x + step_length;
		y = k*exp(a*x);
		grid_points[i].get_Coordinate(x,y);
	}
}

void GridPoints::divide_domain_Quadratic(Point point1, Point point2, int N){
	float a,b,c;
	cout << "Enter the coefficient of x^2" << endl;
	cin >> a;
	cout << "Enter the coefficient of x" << endl;
	cin >> b;
	cout << "Enter the coefficient of x^0" << endl;
	cin >> c;
	float x,y,step_length;
	step_length = (point2.get_x_coordinate() - point1.get_x_coordinate())/(N + 1);
	x = point1.get_x_coordinate();
	grid_points = new Point[N];
	for (int i = 0; i < N; i++){
		x = x + step_length;
		y = a*x*x + b*x + c;
		grid_points[i].get_Coordinate(x,y);
	}
}

bool GridPoints::get_direction(){
	cout << "0. Inward" << endl;
	cout << "1. Outward" << endl;
	bool choice;
	cin >> choice;
	return choice;
}

void GridPoints::Linear_Grid(Point point1, Point point2, int N){
	divide_domain_Line(point1,point2, N);
}

void GridPoints::Elliptic_Grid(Point point1, Point point2, int N){
	bool direction = get_direction();
	divide_domain_Ellipse(point1, point2, N, direction);
}

void GridPoints::Circular_Grid(Point point1, Point point2, int N){
	bool direction = get_direction();
	divide_domain_Circle(point1, point2,N,direction);
}

void GridPoints::Parabolic_Grid(Point point1,Point point2,int N){
	divide_domain_Parabola(point1,point2,N);
}

void GridPoints::Exponential_Grid(Point point1, Point point2, int N){
	divide_domain_exponential(point1, point2, N);
}

void GridPoints::Quadratic_Grid(Point point1, Point point2, int N){
	divide_domain_Quadratic(point1,point2, N);
}
