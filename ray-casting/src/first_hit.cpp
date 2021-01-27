#include "first_hit.h"
#include "first_hit.h"
#include <iostream>

bool first_hit(
  const Ray & ray, 
  const double min_t,
  const std::vector< std::shared_ptr<Object> > & objects,
  int & hit_id, 
  double & t,
  Eigen::Vector3d & n)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  int min_obj_id = -1;
  double min_obj_t = std::numeric_limits<double>::infinity();
  Eigen::Vector3d min_n;

  for (int i = 0; i < objects.size(); ++i) {
    double curr_t;
    Eigen::Vector3d curr_n;

    bool hasInteract = objects[i]->intersect(ray, min_t, curr_t, curr_n);
    if (hasInteract){
      if (curr_t < min_obj_t) {
        min_obj_t = curr_t;
        min_n = curr_n;
        min_obj_id = i;
      }
    }
  }
  // check if a hit was found
  if (min_obj_id != -1){
    hit_id = min_obj_id;
    t = min_obj_t;
    n = min_n;
    return true;
  }
  return false;
  ////////////////////////////////////////////////////////////////////////////
}

