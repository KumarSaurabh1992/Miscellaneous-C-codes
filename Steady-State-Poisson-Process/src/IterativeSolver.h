//! This class solves the linear equation AX = B
/*! @author Kumar Saurabh (MA14M004)*/


#ifndef ITERATIVESOLVER_H_
#define ITERATIVESOLVER_H_
#include "SparseMatrix.h"

class Iterative_Solver {
	Vector<double> temp;
	double cal_error(Vector<double>& X, Vector<double> &X1);
	void ILUDecomposition(SparseMatrix & spm);
	void forward_substitution(SparseMatrix &, Vector<double> &, Vector <double> &);
	void backward_substitution(SparseMatrix &, Vector<double> &, Vector <double> &);
	void forward_substitution_Gauss_Siedel(SparseMatrix &, Vector<double> &, Vector <double> &);
public:
	void Gauss_Siedel(SparseMatrix & spm, Vector<double> & X, Vector<double> & B);
		void CG(SparseMatrix & spm,Vector<double> & X, Vector<double> & B);
	void BiCG(SparseMatrix &spm,Vector<double> &X,Vector<double> &B);
	void BiCG_preconditioner(SparseMatrix &, Vector<double> & ,Vector <double> &, int);

};

#endif /* ITERATIVESOLVER_H_ */
