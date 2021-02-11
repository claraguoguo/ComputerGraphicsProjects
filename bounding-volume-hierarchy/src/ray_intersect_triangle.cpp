#include "ray_intersect_triangle.h"
#include <Eigen/Dense>
#include <iostream>
bool ray_intersect_triangle(
  const Ray & ray,
  const Eigen::RowVector3d & A,
  const Eigen::RowVector3d & B,
  const Eigen::RowVector3d & C,
  const double min_t,
  const double max_t,
  double & t)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  t = 0;
  
  Eigen::Vector3d t1 = B - A;
  Eigen::Vector3d t2 = B - C;

  Eigen::Matrix3d A_matrix;
  Eigen::Vector3d b;

  // std::cout << t1<< std::flush;
  // Reference: textbook page 78 - 4.4.2 Ray-Triangle Intersection
  A_matrix << t1.x(), t2.x(), ray.direction.x(),   
       t1.y(), t2.y(), ray.direction.y(),
       t1.z(), t2.z(), ray.direction.z();
  b = B.transpose() - ray.origin;

  // Solve for linear system equation
  Eigen::Vector3d x = A_matrix.colPivHouseholderQr().solve(b);

  double alpha = x(0);
  double beta = x(1);
  t = x(2);

  // check if alpha, beta, t are valid
  if (t < min_t || t >= max_t || alpha < 0 || beta < 0 || alpha + beta > 1) return false;

  return true;
    ////////////////////////////////////////////////////////////////////////////
}

