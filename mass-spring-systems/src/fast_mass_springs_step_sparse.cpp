#include "fast_mass_springs_step_sparse.h"
#include <igl/matlab_format.h>

void fast_mass_springs_step_sparse(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & E,
  const double k,
  const Eigen::VectorXi & b,
  const double delta_t,
  const Eigen::MatrixXd & fext,
  const Eigen::VectorXd & r,
  const Eigen::SparseMatrix<double>  & M,
  const Eigen::SparseMatrix<double>  & A,
  const Eigen::SparseMatrix<double>  & C,
  const Eigen::SimplicialLLT<Eigen::SparseMatrix<double> > & prefactorization,
  const Eigen::MatrixXd & Uprev,
  const Eigen::MatrixXd & Ucur,
  Eigen::MatrixXd & Unext)
{
  //////////////////////////////////////////////////////////////////////////////
  // Replace with your code
  double penalty_weight = 1e10;
  Eigen::MatrixXd d, y, b_penalty, updated_p;

  updated_p = Ucur;
  for(int iter = 0; iter < 50; iter++)
  {
    d = Eigen::MatrixXd::Zero(r.size(), V.cols());
    int i, j;
    for (int row = 0; row < r.size(); ++row) {
      i = E(row, 0);
      j = E(row, 1);
      d.row(row) = r(row)*(updated_p.row(i) - updated_p.row(j)).normalized();
    }

    y = (1.0/pow(delta_t, 2))*M*(2*Ucur - Uprev) + fext;
    b_penalty = k*A.transpose()*d + y + penalty_weight*C.transpose()*C*V; 
    updated_p = prefactorization.solve(b_penalty);
  }

  Unext = updated_p;
  //////////////////////////////////////////////////////////////////////////////
}
