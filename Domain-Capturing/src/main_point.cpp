///*
// * main_point.cpp
// *
// *  Created on: Jan 22, 2015
// *      Author: saurabh
// */
//
#include <iostream>
#include <fstream>
#include "Point.h"
#include "Domain.h"
#include "GridPoints.h"
#include "Boundary.h"
using namespace std;

int main()
{
	int N;
	cout << "Enter the number of points for boundary of domain";
	cin >> N;
	Boundary bps;
	bps.set_size(N);
	bps.set_Boundary_Points();
	bps.set_number_of_initial_compartments(N);
	int desire;
	ofstream fout("Points.txt");
	while (1){
		cout << "*****************************" << endl;
		cout << "Enter what do you want" << endl;
		cout << "1. Divide domain into grids" << endl;
		cout << "2. Check which curve have you drawn between the two set of points" << endl;
		cout << "3. Number of Compartments" << endl;
		cout << "-1.Exit" << endl;
		cout << "****************************" << endl;
		cin >> desire;
		if (desire == 1){
			bps.display_points();
			bps.make_grid_choice(fout);
		}
		else if (desire == 2){
			bps.display_which_curve();
		}
		else if (desire == 3){
			cout << bps.get_number_of_compartments() << endl;
		}
		else if (desire == -1){
			break;
		}
		else{
			cout << "Wrong choice" << endl;
			cout << "Reenter your choice" << endl;
		}

	}
	fout.close();
	return 0;
}


