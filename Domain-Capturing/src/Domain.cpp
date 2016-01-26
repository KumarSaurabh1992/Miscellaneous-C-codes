/*
 * Domain.cpp
 *
 *  Created on: Jan 22, 2015
 *      Author: saurabh
 */

#include "Domain.h"
#include "Point.h"
#include "Vector.h"
#include <iostream>
using namespace std;

void Domain::set_compartment_number(int i,int j){
	if ( i < j){
		compartment_number = i;
	}
	else{
		compartment_number = j;
	}
}

int Domain::get_compartment_number(){
	return compartment_number;
}

void Domain::set_end(int i){
	end = i;
}

int Domain::get_end(){
	return end;
}

void Domain::set_curve(int i){
	curve_start = i;
}

int Domain::get_curve(){
	return curve_start;
}

void Domain::set_index(int i){
	index = i;
}

int Domain::get_index(){
	return index;
}

