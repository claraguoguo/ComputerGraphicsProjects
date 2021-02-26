#include "per_corner_normals.h"
#include "triangle_area_normal.h"
// Hint:
#include "vertex_triangle_adjacency.h"
#include <iostream>
#include <math.h>

void per_corner_normals(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  const double corner_threshold,
  Eigen::MatrixXd & N)
{
  N = Eigen::MatrixXd::Zero(F.rows()*3,3);
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here:
  std::vector<std::vector<int>> VF;
  vertex_triangle_adjacency(F, V.rows(), VF);

  Eigen::RowVector3d normal_weighted_sum, general_norm, curr_norm;
  for (int i = 0; i < F.rows(); ++i) {
    normal_weighted_sum = Eigen::RowVector3d(0, 0, 0);
    general_norm = triangle_area_normal(
      V.row(F(i, 0)), V.row(F(i, 1)), V.row(F(i, 2)));
    for (int j = 0; j < F.cols(); ++j){
      for (auto & face : VF[F(i, j)]) {
        curr_norm = triangle_area_normal(
          V.row(F(face, 0)), V.row(F(face, 1)), V.row(F(face, 2)));

        // Compute the difference between curr_norm (unit vector) and normal_weighted_sum
        double diff_angle = acos(abs(curr_norm.normalized().dot(general_norm.normalized())));
        // Convert from radians to degree
        diff_angle = diff_angle*180/M_PI;
        // Use curr_norm, if diff_angle is larger than threshold
        if(diff_angle > corner_threshold) {
          normal_weighted_sum += curr_norm;
        }
      }
      N.row(i*3 + j) = normal_weighted_sum.normalized();
    }
  }
  ////////////////////////////////////////////////////////////////////////////
}
