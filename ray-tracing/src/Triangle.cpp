#include "Triangle.h"
#include "Ray.h"
#include <iostream>
#include <Eigen/Dense>

bool Triangle::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  Eigen::Vector3d pt1 = std::get<0>(corners); 
  Eigen::Vector3d pt2 = std::get<1>(corners); 
  Eigen::Vector3d pt3 = std::get<2>(corners); 

  Eigen::Vector3d t1 = pt2 - pt1;
  Eigen::Vector3d t2 = pt2 - pt3;

  Eigen::Matrix3d A;
  Eigen::Vector3d b;

  // Reference: textbook page 78 - 4.4.2 Ray-Triangle Intersection
  A << t1.x(), t2.x(), ray.direction.x(),   
       t1.y(), t2.y(), ray.direction.y(),
       t1.z(), t2.z(), ray.direction.z();
  b = pt2 - ray.origin;

  // Solve for linear system equation
  Eigen::Vector3d x = A.colPivHouseholderQr().solve(b);

  double alpha = x(0);
  double beta = x(1);
  t = x(2);

  // check if alpha, beta, t are valid
  if (t < min_t || alpha < 0 || beta < 0 || alpha + beta > 1) return false;

  // compute normal unit vector
  n = t2.cross(t1);
  n.normalize();
  return true;
  ////////////////////////////////////////////////////////////////////////////
}


