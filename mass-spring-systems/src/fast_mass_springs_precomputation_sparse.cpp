#include "fast_mass_springs_precomputation_sparse.h"
#include "signed_incidence_matrix_sparse.h"
#include <vector>

bool fast_mass_springs_precomputation_sparse(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & E,
  const double k,
  const Eigen::VectorXd & m,
  const Eigen::VectorXi & b,
  const double delta_t,
  Eigen::VectorXd & r,
  Eigen::SparseMatrix<double>  & M,
  Eigen::SparseMatrix<double>  & A,
  Eigen::SparseMatrix<double>  & C,
  Eigen::SimplicialLLT<Eigen::SparseMatrix<double> > & prefactorization)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code
  std::vector<Eigen::Triplet<double> > ijv, ijv_2;
  const int n = V.rows();
  Eigen::SparseMatrix<double> Q(n,n);

  // Compute list of edge lengths (#E)
  r = Eigen::VectorXd::Zero(E.rows());
  for (int row = 0; row < E.rows(); ++row) {
    int i = E(row, 0);
    int j = E(row, 1);
    r(row) = (V.row(i) - V.row(j)).norm();
  }

  // Compute mass matrix (#V by #V)
  for (int i = 0; i < n; ++i) {
    ijv.emplace_back(i, i, m(i));
  }
  M.resize(n, n);
  M.setFromTriplets(ijv.begin(),ijv.end());
  
  // Compute signed incidence matrix
  signed_incidence_matrix_sparse(n, E, A);

  // Compute selection matrix (#b by #V)
  // C has one row per pinned vertex with '+1' in the corresponding column
  for (int i = 0; i < b.size(); ++i) {
    ijv_2.emplace_back(i, b(i), 1.0);
  }
  C.resize(b.size(), n);
  C.setFromTriplets(ijv_2.begin(),ijv_2.end());
  
  // Compute energy's quadratic matrix with penalty term
  double penalty_weight = 1.0e10;
  Q = k*A.transpose()*A + (1.0/pow(delta_t, 2))*M + penalty_weight*C.transpose()*C;

  /////////////////////////////////////////////////////////////////////////////
  prefactorization.compute(Q);
  return prefactorization.info() != Eigen::NumericalIssue;
}
