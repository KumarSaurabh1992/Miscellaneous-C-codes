/*
 * Boundary.h
 *
 *  Created on: Jan 25, 2015
 *      Author: saurabh
 */

#ifndef BOUNDARY_H_
#define BOUNDARY_H_

#include "Domain.h"
#include "Point.h"
#include "GridPoints.h"
#include <fstream>
using namespace std;

class Boundary {
	int number_of_points;
	int number_of_compartments;
	int get_compartment(int i);
	void post_grid_opeartion(int index1,int index2,int choice);

public:
	Domain *points;
	void set_size(int N);
	void set_Boundary_Points();
	int get_number_of_points();
	void display_points();
	void boundary_choices();
	void display_boundary_points(int index1, int index2);
	void display_which_curve();
	void set_number_of_compartments(int i,int j);
	void set_number_of_initial_compartments(int N);
	int get_number_of_compartments();
	void make_grid_choice(ofstream & outfile);
};

#endif /* BOUNDARY_H_ */
