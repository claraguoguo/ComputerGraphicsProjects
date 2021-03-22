#include "signed_incidence_matrix_sparse.h"
#include <vector>

void signed_incidence_matrix_sparse(
  const int n,
  const Eigen::MatrixXi & E,
  Eigen::SparseMatrix<double>  & A)
{
  //////////////////////////////////////////////////////////////////////////////
  // Replace with your code
  std::vector<Eigen::Triplet<double> > ijv;
  for (int row = 0; row < E.rows(); ++row) {
    int i = E(row, 0);
    int j = E(row, 1);
    ijv.emplace_back(row, i, 1.0);
    ijv.emplace_back(row, j, -1.0);
  }
  A.resize(E.rows(),n);
  A.setFromTriplets(ijv.begin(),ijv.end());
  //////////////////////////////////////////////////////////////////////////////
}
