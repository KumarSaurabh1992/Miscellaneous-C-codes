/*
 * Point.h
 *
 *  Created on: Jan 22, 2015
 *      Author: saurabh
 */

#ifndef POINT_H_
#define POINT_H_

class Point {
	float coordinate_x;
	float coordinate_y;
//	int compartment_number;
public:
	void get_Coordinate(float x, float y);
	float get_x_coordinate();
	float get_y_coordinate();
	void get_Point();
	void display();
//	int get_compartment_number();
//	int set_compartment_number();


};

#endif /* POINT_H_ */
