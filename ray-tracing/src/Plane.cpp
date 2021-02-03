#include "Plane.h"
#include "Ray.h"
#include <iostream>
bool Plane::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  
  // check if ray.direction and normal is perpendicular (ray is parallel to plane)
  if (normal.dot(ray.direction) == 0) {
    return false;
  }

  double dis = ((-1*normal).dot(ray.origin - point))/(normal.dot(ray.direction));
  if (dis > min_t && dis > 1){
    t = dis;
    n = normal;
    return true;
  }
  return false;
  ////////////////////////////////////////////////////////////////////////////
}

