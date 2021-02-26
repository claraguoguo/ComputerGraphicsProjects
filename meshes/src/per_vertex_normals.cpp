#include "per_vertex_normals.h"
#include "triangle_area_normal.h"
#include <unordered_map>
#include "vertex_triangle_adjacency.h"

void per_vertex_normals(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  Eigen::MatrixXd & N)
{
  N = Eigen::MatrixXd::Zero(V.rows(),3);
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here:

  // For each vertex store a list of all incident faces.
  std::vector<std::vector<int>> VF;
  vertex_triangle_adjacency(F, V.rows(), VF);

  for (int vertex = 0; vertex < V.rows(); ++vertex) {
    Eigen::RowVector3d normal_weighted_sum = Eigen::RowVector3d(0, 0, 0); 
    for (auto & face : VF[vertex]) {
      Eigen::RowVector3d curr_norm = triangle_area_normal(
        V.row(F(face, 0)), V.row(F(face, 1)), V.row(F(face, 2)));
      // normal_sum is weighted sum
      normal_weighted_sum += curr_norm;
    }
    N.row(vertex) = normal_weighted_sum.normalized();
  }

  ////////////////////////////////////////////////////////////////////////////
}
