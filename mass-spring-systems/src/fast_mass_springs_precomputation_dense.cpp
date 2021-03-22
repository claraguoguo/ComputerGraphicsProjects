#include "fast_mass_springs_precomputation_dense.h"
#include "signed_incidence_matrix_dense.h"
#include <Eigen/Dense>

bool fast_mass_springs_precomputation_dense(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & E,
  const double k,
  const Eigen::VectorXd & m,
  const Eigen::VectorXi & b,
  const double delta_t,
  Eigen::VectorXd & r,
  Eigen::MatrixXd & M,
  Eigen::MatrixXd & A,
  Eigen::MatrixXd & C,
  Eigen::LLT<Eigen::MatrixXd> & prefactorization)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code
  Eigen::MatrixXd Q = Eigen::MatrixXd::Identity(V.rows(),V.rows());

  // Compute list of edge lengths (#E)
  r = Eigen::VectorXd::Zero(E.rows());
  for (int row = 0; row < E.rows(); ++row) {
    int i = E(row, 0);
    int j = E(row, 1);
    r(row) = (V.row(i) - V.row(j)).norm();
  }

  // Compute mass matrix (#V by #V)
  M = Eigen::MatrixXd::Zero(V.rows(), V.rows());
  for (int row = 0; row < V.rows(); ++row) {
    M(row, row) = m(row);
  }

  // Compute signed incidence matrix (#E by #V)
  signed_incidence_matrix_dense(V.rows(), E, A);

  // Compute selection matrix (#b by #V)
  // C has one row per pinned vertex with '+1' in the corresponding column
  C = Eigen::MatrixXd::Zero(b.size(), V.rows());
  for (int row = 0; row < b.size(); ++row) {
    C(row, b(row)) = 1.0;
  }
  
  // Compute energy's quadratic matrix with penalty term
  double penalty_weight = 1.0e10;
  Q = k*A.transpose()*A + (1.0/pow(delta_t, 2))*M + penalty_weight*C.transpose()*C;

  /////////////////////////////////////////////////////////////////////////////
  prefactorization.compute(Q);
  return prefactorization.info() != Eigen::NumericalIssue;
}
