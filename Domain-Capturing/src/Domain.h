/*
 * Domain.h
 *
 *  Created on: Jan 22, 2015
 *      Author: saurabh
 */

#ifndef DOMAIN_H_
#define DOMAIN_H_
#include "Point.h"

class Domain : public Point{
	int compartment_number;
	int end;
	int curve_start;
	int index;
public:
	int get_compartment_number();
	void set_compartment_number(int i,int j);
	void set_end(int i);
	int get_end();
	void set_curve(int i);
	int get_curve();
	void set_index(int i);
	int get_index();
};

#endif /* DOMAIN_H_ */
