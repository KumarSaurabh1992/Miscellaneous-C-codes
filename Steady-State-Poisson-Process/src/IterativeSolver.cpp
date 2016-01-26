/*
 * IterativeSolver.cpp
 *
 *  Created on: Jan 30, 2015
 *      Author: saurabh
 */

#include "IterativeSolver.h"
#include <math.h>
#include <fstream>
#include "SparseMatrix.h"
#include <time.h>
//! Solves AX = B with Gauss Seidel Method
/*! @param spm Matrix A in sparse format */
/*! @param X Vector x */
/*! @param B Vector B*/
/*! This code can be used in following way: */
/*! relaxation parameter: Between 0 and 1: under relaxation*/
/*! relaxation parameter 1: No relaxation*/
/*! relaxation parameter: Between 1 and 2 Over relaxation*/
/*! The value of relaxation is asked by user at the runtime*/
void Iterative_Solver::Gauss_Siedel(SparseMatrix & spm, Vector<double> & X, Vector<double> & B){
	int row, col;
	Vector<double> temp;
	double sum;
	temp.set_size(X.get_size());
	double error = 10;
	cout << "Enter the relaxation parameter" << endl;
	cout << "For under-relaxation between 0 and 1" << endl;
	cout << "For no relaxation 1" << endl;
	cout << "For over-relaxation and fast convergence between 1 and 2" << endl;
	float relax;
	cin >> relax;
	int number_of_iteration = 0;
	while (error > pow(10.0,-6)){

		for(int i = 0; i < X.get_size();i ++){
			temp[i] = X[i];
		}

		for(int i = 0; i < spm.get_row_size(); i++){
			row = i;
			sum = 0.0;
			for(int j = spm.get_I(i); j < spm.get_I(i+1); j++){
				col = spm.get_J(j);
				if(col != row){
					sum += spm.get_non_zero_Elements(j)*X[col];
				}
			}
			X[row] =  -relax*X[row] +relax*(((B[row] - sum)/(spm.getValue(row,row))));

		}
		//		cout << "*************";
		//					temp.display();
		//					cout <<"*************";
		//					X.display();
		error = cal_error(X,temp);
		//	temp.A = X.A;
		number_of_iteration++;
		if((number_of_iteration % 100) == 0){
			cout << "Iteration number " << number_of_iteration << " completed " << endl;
		}
	}
	cout << "Solution converged after " << number_of_iteration << "  from Gauss Siedel"<< endl;
	cout << "Writing in file" << endl;
	ofstream fout("solver.txt");

	for(int i = 0; i < X.get_size(); i++){
		fout << X[i] << endl;
	}
	fout.close();
	cout << "File Written" << endl;
}

//! This calculates the error based on the relative difference between two points
/*! @param X Vector X */
/*! @param X1 Vector X1*/

double Iterative_Solver::cal_error(Vector<double> &X, Vector<double> &X1){
	double err = 0.0;
	for (int i = 0; i < X.get_size(); i++){
		if (fabs(X[i] - 0.0) > pow(10.0,-6)){
			if (err <  fabs((X[i] - X1[i])/X[i])){
				err = fabs((X[i] - X1[i])/X[i]);
			}

		}

	}
	//	cout << err << endl;
	return err;
}


void Iterative_Solver::CG(SparseMatrix & spm,Vector<double> & X,Vector<double> & B){
	int number_of_iterations = 0;
	Vector<double> Q;
	Q.set_size(X.get_size());
	Q.initialize();
	spm.multiply(X,Q);
//	Q = spm*X;
	Vector<double> r;
	r.set_size(X.get_size());
	r.sub(B,Q);
//	r = B - Q;
//	Q.del();
//	cout << "Reached 1"<<endl;
	Vector<double> d;
	d.set_size(X.get_size());
	d.copy_values(r);
	double rnew,alpha,rold,beeta;
	rnew = r*r;
	double error = 199;
	Vector<double> temp;
	temp.set_size(X.get_size());
	Vector<double> q;
	q.set_size(X.get_size());
	Vector<double> temp1;
	temp1.set_size(X.get_size());
	temp1.initialize();
	while(error > pow(10.0,-6)){

		temp.copy_values(X);
		spm.multiply(d,q);
//		q = spm*d;
		alpha = rnew/(d*q);
		X.add(X,d,alpha);
//		X = X + (d*alpha);
		r.add(r,q,-alpha);
//		r = r - (q*alpha);
		rold = rnew;
		rnew = r*r;
		beeta = rnew/rold;
		d.add(r,d,beeta);
//		d = r + (d*beeta);
		error = cal_error(X,temp);
		number_of_iterations++;
//		temp.del();


	}
	cout << "Solution Converged from Conjugate Gradient after " << number_of_iterations << " iterations" << endl;

}

//! Solves AX = B with BiConjugate Gradient  Method
/*! @param spm Matrix A in sparse format */
/*! @param X Vector x */
/*! @param B Vector B*/
/*! This code doesn't make use of any preconditioner*/
void Iterative_Solver::BiCG(SparseMatrix &spm,Vector <double> &X,Vector<double> &B){
	clock_t time;
	time = clock();
	int number_of_iterations = 0;
	Vector<double> Q;
	Q.set_size(X.get_size());
	Q.initialize();
	spm.multiply(X,Q);
	//	Q = spm*X;
	Vector<double> r;
	r.set_size(X.get_size());
	r.sub(B,Q);
	//	r = B - Q;
	Vector<double> r_star;
	r_star.set_size(X.get_size());
	r_star.copy_values(r);
	double beeta;
	double alpha = 1.0;
	double rho = 1.0;
	double omega = 1.0;
	//	double p1 = 0.0;
	double error = 199;
	Vector<double> temp;
	temp.set_size(X.get_size());
	temp.initialize();
	Vector<double> p1;
	p1.set_size(X.get_size());
	p1.initialize();
	Vector<double> v;
	v.set_size(X.get_size());
	v.initialize();
	Vector<double> s;
	s.set_size(X.get_size());
	s.initialize();
	Vector<double> t;
	t.set_size(X.get_size());
	t.initialize();
	Vector<double> temp1;
	temp1.set_size(X.get_size());
	temp1.initialize();
	//	cout << "Line 145" << endl;
	cout << "Iterations started" << endl;
	while(error > pow(10.0,-6)){
		temp.copy_values(X);
		//		cout << "Line 148" << endl;
		double rho_1 = r_star*r;
		//		cout << "Line 150" <<endl;
		beeta = (rho_1/rho)*(alpha/omega);
		//		cout << "Line 151" << endl;
		temp1.add(p1,v,-omega);
		//		p1 = r + (p1 - v*omega)*beeta;
		p1.add(r,temp1,beeta);

		//		cout << "Line 153";
		spm.multiply(p1,v);
		//		v = spm*p1;
		//		cout << "*******" << endl;
		//		v.display();
		alpha = rho_1/(r_star*v);
		//		cout << "Line 159";
		s.add(r,v,-alpha);
		//		cout << "Line 161";
		//		s = r - v*alpha;
		spm.multiply(s,t);
		//		t.display();
		//		cout << "Line 164";
		//		t = spm*s;
		double tempval1 = t*s;
		double tempval2 = t*t;
		//		t.display();
		//		cout << tempval1 << endl;
		//		cout << tempval2 << endl;


		omega = (tempval1)/(tempval2);

		//		cout << "Line 167" << endl;
		//		temp1.initialize();
		temp1.add(X,p1,alpha);
		X.add(temp1,s,omega);
		//		temp1.initialize();
		//		X = X + s*omega + p1*alpha;
		r.add(s,t,-omega);
		//		r = s - t*omega;
		rho = rho_1;
		//		cout << "Line 189" <<endl;
		error = cal_error(X,temp);
//		cout << error << endl;
		number_of_iterations++;
		if((number_of_iterations % 100) == 0){
					cout << "Iteration number " << number_of_iterations << "completed " << endl;
				}
	}

	cout << "Error in calculation " << error << endl;
	cout << "Solution Converged from BiConjugate Gradient without any preconditioner after " << number_of_iterations << " iterations" << endl;
	time = clock() - time;
	cout << "Time taken by BiCG without any preconditioner is  " << ((float)time)/CLOCKS_PER_SEC << "seconds" << endl;
	//	X.display();
	//	return X;
	cout << "Writing in file" << endl;
	ofstream fout("solver.txt");
	for(int i = 0; i < X.get_size(); i++){
		fout << X[i] << endl;
	}
	fout.close();
	cout << "File Written" << endl;
	//	return;

}

//! Computes the ILU Decomposition of the Matrix A in the sparse form
/*! @param spm Matrix A in the sparse form*/

void Iterative_Solver::ILUDecomposition(SparseMatrix & spm){
	int ROW,COL_k,COL_j;
	int col_start,col_end,col_med;
	for (int i = 1; i < spm.get_row_size(); i++){
		ROW = i;
		col_start = spm.get_I(i);
		col_end = spm.get_I(i + 1);
		COL_k = spm.get_J(col_start);
		//		cout << COL_k << endl;
		while(COL_k < ROW){

			double temp = spm.getValue(ROW,COL_k)/spm.getValue(COL_k,COL_k);
			spm.update_matrix_ILU(temp,ROW,COL_k);
			col_med = col_start + 1;
			COL_j = spm.get_J(col_med);

			while (col_med < col_end){
				//				cout << "Entered";
				double temp2 = spm.getValue(ROW,COL_j) - spm.getValue(ROW,COL_k)*spm.getValue(COL_k,COL_j);
				spm.update_matrix_ILU(temp2,ROW,COL_j);
				col_med++;
				COL_j = spm.get_J(col_med);
			}

			col_start++;
			COL_k = spm.get_J(col_start);
		}

	}
	//	spm.display();

}

//! Solves AX = B with by forward substitution
/*! @param spm Matrix A in sparse format and is Lower Triangular Matrix */
/*! @param X Vector x */
/*! @param B Vector B*/
void Iterative_Solver::forward_substitution(SparseMatrix & spm, Vector<double> & X, Vector<double> & B){
	int ROW, COL;
	for(int i = 0; i < B.get_size(); i++){
		ROW = i;
		double sum = 0.0;
		int j = spm.get_I(i);
		do{

			COL = spm.get_J(j);

			if (COL == ROW){
				X[i] = (B[i] - sum)/1.0;
			}
			else if (COL < ROW)	{
				sum += spm.getValue(ROW,COL)*X[COL];
			}
			j++;
		}while(COL < ROW);
		//		for(int j = spm.get_I()[i]; j < spm.get_I()[i + 1]; j++){
		//
		//			COL = spm.get_J()[j];
		//
		//			if (COL == ROW){
		//				X[i] = (B[i] - sum)/1.0;
		//			}
		//			else if (COL < ROW)
		//			{
		//				sum += spm.getValue(ROW,COL)*X[COL];
		////				cout << "Row number \t" << ROW << "Column number \t" << COL << "\t" << spm.getValue(ROW,COL) << "\t"<< X[COL]<<endl;
		//			}
		//
		//		}
	}
	//	X.display();
}

//! Solves AX = B with by backward substitution
/*! @param spm Matrix A in sparse format and is Upper Triangular Matrix */
/*! @param X Vector x */
/*! @param B Vector B*/
void Iterative_Solver::backward_substitution(SparseMatrix  & spm,Vector<double>  & X, Vector<double> & B){
	int ROW, COL;
	for(int i = B.get_size() - 1; i >= 0; i--){
		ROW = i;
		double sum = 0.0;
		int j = spm.get_I(i + 1) - 1;
		do{

			COL = spm.get_J(j);
			if (COL == ROW){
				X[i] = (B[i] - sum)/spm.getValue(ROW,COL);
			}
			else if(COL > ROW){
				sum += spm.getValue(ROW,COL)*X[COL];
			}
			j--;
		}while(COL > ROW);
		//		for(int j = spm.get_I()[i + 1] - 1; j >= spm.get_I()[i]; j--){
		//			COL = spm.get_J()[j];
		//			if (COL == ROW){
		//				X[i] = (B[i] - sum)/spm.getValue(ROW,COL);
		//			}
		//			else if(COL > ROW){
		//				sum += spm.getValue(ROW,COL)*X[COL];
		//			}
		//		}
	}
}
//! Solves AX = B with by forward substitution for Gauss Seidel Preconditioner
/*! @param spm Matrix A in sparse format and is Lower Triangular Matrix */
/*! @param X Vector x */
/*! @param B Vector B*/
void Iterative_Solver::forward_substitution_Gauss_Siedel(SparseMatrix & spm, Vector<double> & X, Vector<double> & B){
	int ROW, COL;
	for(int i = 0; i < B.get_size(); i++){
		ROW = i;
		double sum = 0.0;
		int j = spm.get_I(i);
		do{

			COL = spm.get_J(j);

			if (COL == ROW){
				X[i] = (B[i] - sum)/spm.getValue(ROW,COL);
			}
			else if (COL < ROW)	{
				sum += spm.getValue(ROW,COL)*X[COL];
			}
			j++;
		}while(COL < ROW);
	}
}
//! Solves AX = B with Biconjugate preconditioner
/*! @param spm Matrix A in sparse format */
/*! @param X Vector X */
/*! @param B Vector B*/
/*! @param choice the type of preconditioner*/
/*! This code uses three preconditioner: */
/*! 1. Jacobi preconditioner */
/*! 2. ILU preconditioner*/
/*! 3. Gauss Sedel preconditioner*/
/*! The type of preconditioner is asked by the user at the runtime*/
void Iterative_Solver::BiCG_preconditioner(SparseMatrix & spm, Vector<double> & X, Vector <double> & B, int choice){
	clock_t time;
	time = clock();
	int number_of_iterations = 0;
	Vector<double> Q;
	Q.set_size(X.get_size());
	Q.initialize();
	spm.multiply(X,Q);
	//	Q = spm*X;
	Vector<double> r;
	r.set_size(X.get_size());
	r.sub(B,Q);
	//	r = B - Q;
	Vector<double> r_star;
	r_star.set_size(X.get_size());
	r_star.copy_values(r);
	double beeta;
	double alpha = 1.0;
	double rho = 1.0;
	double omega = 1.0;
	//	double p1 = 0.0;
	double error = 199;
	Vector<double> temp;
	temp.set_size(X.get_size());
	temp.initialize();
	Vector<double> p1;
	p1.set_size(X.get_size());
	p1.initialize();
	Vector<double> v;
	v.set_size(X.get_size());
	v.initialize();
	Vector<double> s;
	s.set_size(X.get_size());
	s.initialize();
	Vector<double> t;
	t.set_size(X.get_size());
	t.initialize();
	Vector<double> temp1;
	temp1.set_size(X.get_size());
	temp1.initialize();
	SparseMatrix M;

	Vector<double> y;
	y.set_size(X.get_size());
	Vector<double> z;
	z.set_size(X.get_size());
	if (choice == 0){
		M.initialize(X.get_size());
		M.extractdiagonal(spm);
	}
	else if (choice == 1){
		M.copy(spm);
		ILUDecomposition(M);

	}
	//	cout << "Line 145" << endl;
	cout << "Iterations started" << endl;
	while(error > pow(10.0,-6)){
		temp.copy_values(X);
		//		cout << "Line 148" << endl;
		double rho_1 = r_star*r;
		//		cout << "Line 150" <<endl;
		beeta = (rho_1/rho)*(alpha/omega);
		//		cout << "Line 151" << endl;
		temp1.add(p1,v,-omega);
		//		p1 = r + (p1 - v*omega)*beeta;
		p1.add(r,temp1,beeta);
		if (choice == 0){
			//			y.multiply_dot(M,p1);
			M.multiply(p1,y);
			//			y.display();
		}

		else if(choice == 1){
			Vector<double> temp_y;
			temp_y.set_size(X.get_size());
			temp_y.initialize();
			forward_substitution(M,temp_y,p1);
			backward_substitution(M,y,temp_y);

		}
		else if(choice == 2){
			forward_substitution_Gauss_Siedel(spm,y,p1);
		}
		//		y.display();
		//		cout << "Line 153";
		spm.multiply(y,v);
		//		v = spm*p1;
		//		cout << "*******" << endl;
		//		v.display();
		alpha = rho_1/(r_star*v);
		//		cout << "Line 159";
		s.add(r,v,-alpha);
		//		cout << "Line 161";
		//		s = r - v*alpha;
		if(choice == 0){
			M.multiply(s,z);
			//			z.multiply_dot(M,s);

		}
		else if (choice == 1){
			Vector<double> temp_z;
			temp_z.set_size(X.get_size());
			temp_z.initialize();
			forward_substitution(M,temp_z,s);
			backward_substitution(M,z,temp_z);
		}
		else if(choice == 2){
			forward_substitution_Gauss_Siedel(spm,z,s);
		}
		spm.multiply(z,t);
		//		t.display();
		//		cout << "Line 164";
		//		t = spm*s;
		double tempval1 = t*s;
		double tempval2 = t*t;
		//		t.display();
		//		cout << tempval1 << endl;
		//		cout << tempval2 << endl;


		omega = (tempval1)/(tempval2);

		//		cout << "Line 167" << endl;
		//		temp1.initialize();
		temp1.add(X,y,alpha);
		X.add(temp1,z,omega);
		//		temp1.initialize();
		//		X = X + s*omega + p1*alpha;
		r.add(s,t,-omega);
		//		r = s - t*omega;
		rho = rho_1;
		//		cout << "Line 189" <<endl;
		error = cal_error(X,temp);
//		cout << error << endl;
		number_of_iterations++;
		if((number_of_iterations % 100) == 0){
			cout << "Iteration number " << number_of_iterations << "completed " << endl;
		}
	}
	cout << "Error in calculation " << error << endl;
	if (choice == 0){
		cout << "Solution Converged from BiConjugate Gradient with Jacobi preconditioner after " << number_of_iterations << " iterations" << endl;
	}
	else if (choice == 1){
		cout << "Solution Converged from BiConjugate Gradient with ILU preconditioner after " << number_of_iterations << " iterations" << endl;
	}
	else if (choice == 2){
		cout << "Solution converged from Biconjugate Gradient with Gauss Seidel preconditioner after " << number_of_iterations << " iterations" <<endl;
	}
	time = clock() - time;
	cout << "Time taken by BiCG with the choice of your preconditioner is  " << ((float)time)/CLOCKS_PER_SEC << "seconds" << endl;

	cout << "Writing in file" << endl;
	ofstream fout("solver.txt");

	for(int i = 0; i < X.get_size(); i++){
		fout << X[i] << endl;
	}
	fout.close();
	cout << "File Written" << endl;
}
