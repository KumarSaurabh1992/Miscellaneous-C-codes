/*
 * Point.cpp
 *
 *  Created on: Jan 22, 2015
 *      Author: saurabh
 */

#include "Point.h"
#include <iostream>
using namespace std;


void Point::get_Coordinate(float x, float y){
	coordinate_x = x;
	coordinate_y = y;

}

float Point::get_x_coordinate(){
	return coordinate_x;
}

float Point::get_y_coordinate(){
	return coordinate_y;
}

void Point::get_Point(){
	float x,y;
	cout << "Enter the coordinates";
	cin >> x;
	cin >> y;
	get_Coordinate(x,y);
}

void Point::display(){
	cout << "(" << get_x_coordinate() << ", " << get_y_coordinate() << ")";
}
