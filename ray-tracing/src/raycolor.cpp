#include "raycolor.h"
#include "first_hit.h"
#include "blinn_phong_shading.h"
#include "reflect.h"

#define MAX_RECURSION 7

bool raycolor(
  const Ray & ray, 
  const double min_t,
  const std::vector< std::shared_ptr<Object> > & objects,
  const std::vector< std::shared_ptr<Light> > & lights,
  const int num_recursive_calls,
  Eigen::Vector3d & rgb)
{
  ////////////////////////////////////////////////////////////////////////////
  if (num_recursive_calls > MAX_RECURSION) return false;

  rgb = Eigen::Vector3d(0,0,0);

  int hit_id;
  double t;
  Eigen::Vector3d n;
  double eps = 1.0e-3;

  bool hasHit = first_hit(ray, min_t, objects, hit_id, t, n);
  if (!hasHit) return false; 

  rgb += blinn_phong_shading(ray, hit_id, t, n, objects, lights);

  // compute the reflection of the incoming ray w.r.t to first hit object
  Ray reflection;
  Eigen::Vector3d hit_point;
  hit_point = ray.direction + t*ray.direction;
  reflection.direction = reflect(ray.direction.normalized(), n);
  reflection.origin = hit_point + eps * reflection.direction;

  Eigen::Vector3d new_rgb(0,0,0);
  if (raycolor(reflection, eps, objects, lights, num_recursive_calls + 1, new_rgb)) {
    // km is mirror reflection
    // formula reference: TxB P87 - 4.8 Ideal Specular Reflection
    Eigen::Vector3d curr_rgb = (objects[hit_id]->material->km.array()*new_rgb.array()).matrix();
    rgb += curr_rgb;
  }
  return true;
  ////////////////////////////////////////////////////////////////////////////
}
