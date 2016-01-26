/*
 * GridPoints.h
 *
 *  Created on: Jan 22, 2015
 *      Author: saurabh
 */

#ifndef GRIDPOINTS_H_
#define GRIDPOINTS_H_
# include "Point.h"
class GridPoints {
	float getAngle(Point point1, Point point2);
	float getRadius(Point point1, Point center);
	void divide_domain_Line(Point point1, Point point2, int N);
	void divide_domain_Circle(Point point1,Point point2, int N, bool direction);
	void divide_domain_Ellipse(Point point1, Point point2,  int N,bool direction);
	void divide_domain_Parabola(Point point1, Point point2,int N);
	void divide_domain_exponential(Point point1, Point point2, int N);
	void divide_domain_Quadratic(Point point1, Point point2, int N);
	bool get_direction();
public:
	Point *grid_points;
	void Linear_Grid(Point point1, Point point2, int N);
	void Circular_Grid(Point point1,Point point2, int N);
	void Elliptic_Grid(Point point1, Point point2,  int N);
	void Parabolic_Grid(Point point1, Point point2,int N);
	void Exponential_Grid(Point point1, Point point2, int N);
	void Quadratic_Grid(Point point1, Point point2, int N);

};

#endif /* GRIDPOINTS_H_ */
