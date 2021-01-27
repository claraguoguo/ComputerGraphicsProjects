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

  // Eigen::Vector3d t1 = pt2 - pt1;
  // Eigen::Vector3d t2 = pt3 - pt1;
  Eigen::Vector3d t1 = pt1 - pt2;
  Eigen::Vector3d t2 = pt3 - pt2;

  Eigen::Matrix3d A;
  Eigen::Vector3d b;

  A << t1.x(), t2.x(), -1*ray.direction.x(),   
       t1.y(), t2.y(), -1*ray.direction.y(),
       t1.z(), t2.z(), -1*ray.direction.z();

  b << ray.origin.x(), ray.origin.y(), ray.origin.z();

  Eigen::Vector3d x = A.fullPivLu().solve(b);

  double relative_error = (A*x - b).norm() / b.norm(); // norm() is L2 norm
  std::cout << "The relative error is:\n" << relative_error << std::endl;


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


