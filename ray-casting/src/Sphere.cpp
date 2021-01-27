#include "Sphere.h"
#include "Ray.h"
#include <Eigen/Geometry>
#include <iostream>
#include <cmath>

bool Sphere::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  Eigen::Vector3d dir = ray.direction;
  double A = dir.dot(dir);
  double B = (2*dir).dot(ray.origin - center);
  double C = (ray.origin - center).dot(ray.origin - center) - radius*radius;

  double discriminant = B*B - 4*A*C;

  if (discriminant > 0) {
    // 2 real solutions
    double t1 = (-1*B + sqrt(discriminant))/(2*A);
    double t2 = (-1*B - sqrt(discriminant))/(2*A);
    
    double smaller_t = std::min(t1, t2);
    double bigger_t = std::max(t1, t2);

    // check for valid roots
    if (smaller_t > min_t && smaller_t > 1){
      t = smaller_t;
    }

    else if (bigger_t > min_t && bigger_t > 1){
      t = bigger_t;
    }
    else {
      std::cout << "Error with computing t in Sphere::intersect" << std::endl;
      return false;
    }

    // compute normal (unit) vector
    if (t > min_t && t > 1){
      n = ray.origin + t*dir - center;
      n = n/radius;
      return true;
    }
  }

  else if (discriminant == 0){
    // 1 real solution
    double t = -1*B/(2*A);

    if (t > min_t && t > 1){
      n = ray.origin + t*dir - center;
      n = n/radius;
      return true;
    } 
  }

  else {
    // no real solution
    return false;
  }

  return false;
  ////////////////////////////////////////////////////////////////////////////
}

