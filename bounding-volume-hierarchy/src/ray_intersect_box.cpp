#include "ray_intersect_box.h"
#include <iostream>

bool ray_intersect_box(
  const Ray & ray,
  const BoundingBox& box,
  const double min_t,
  const double max_t)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  double t_x_min, t_x_max, t_y_min, t_y_max, t_z_min, t_z_max;
  double a_x, a_y, a_z;

  // Reference: Textbook Page-302
  a_x = 1.0/ray.direction.x();
  a_y = 1.0/ray.direction.y();
  a_z = 1.0/ray.direction.z();

  // x-component
  if (a_x >= 0) {
    t_x_min = a_x*(box.min_corner.x() - ray.origin.x());
    t_x_max = a_x*(box.max_corner.x() - ray.origin.x());
  }
  else {
    t_x_min = a_x*(box.max_corner.x() - ray.origin.x());
    t_x_max = a_x*(box.min_corner.x() - ray.origin.x());
  }

  // y-component
  if (a_y >= 0) {
    t_y_min = a_y*(box.min_corner.y() - ray.origin.y());
    t_y_max = a_y*(box.max_corner.y() - ray.origin.y());
  }
  else {
    t_y_min = a_y*(box.max_corner.y() - ray.origin.y());
    t_y_max = a_y*(box.min_corner.y() - ray.origin.y());
  }

  // z-component
  if (a_z >= 0) {
    t_z_min = a_z*(box.min_corner.z() - ray.origin.z());
    t_z_max = a_z*(box.max_corner.z() - ray.origin.z());
  }
  else {
    t_z_min = a_z*(box.max_corner.z() - ray.origin.z());
    t_z_max = a_z*(box.min_corner.z() - ray.origin.z());
  }

  // Check if t's are valid
  double lower_bound = std::max(std::max(t_x_min, t_y_min), t_z_min);
  double upper_bound = std::min(std::min(t_x_max, t_y_max), t_z_max);

  // Check if the range is valid && the intersection is within the box.
  bool isValid = lower_bound < upper_bound
                 && std::max(min_t, lower_bound) < std::min(max_t, upper_bound); 

  if (!isValid) return false;

  return true;
  ////////////////////////////////////////////////////////////////////////////
}
