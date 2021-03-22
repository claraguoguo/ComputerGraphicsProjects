#include "signed_incidence_matrix_dense.h"

void signed_incidence_matrix_dense(
  const int n,
  const Eigen::MatrixXi & E,
  Eigen::MatrixXd & A)
{
  //////////////////////////////////////////////////////////////////////////////
  // Replace with your code
  A = Eigen::MatrixXd::Zero(E.rows(),n);

  for (int row = 0; row < E.rows(); ++row) {
    int i = E(row, 0);
    int j = E(row, 1);
    A(row, i) = 1.0; 
    A(row, j) = -1.0; 
  }
  //////////////////////////////////////////////////////////////////////////////
}
