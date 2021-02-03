#include "blinn_phong_shading.h"
// Hint:
#include "first_hit.h"
#include <iostream>
#include <cmath>

Eigen::Vector3d blinn_phong_shading(
  const Ray & ray,
  const int & hit_id, 
  const double & t,
  const Eigen::Vector3d & n,
  const std::vector< std::shared_ptr<Object> > & objects,
  const std::vector<std::shared_ptr<Light> > & lights)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  Eigen::Vector3d L(0,0,0);
  Eigen::Vector3d hit_point = ray.origin + t*ray.direction;
  double eps = 1.0e-6;

  // Ambient component
  // Use a hard-coded value of ia=0.1 for ambient light
  L += 0.1*objects[hit_id]->material->ka;

  for (std::shared_ptr<Light> light : lights) {

    // Direction of the ray from hit point to light
    Eigen::Vector3d pt_to_light_dir; 
    // Distance from hit point to light
    double pt_to_light_dist;
    // Get the distance and direction of the vector from the hit point to light source
    light->direction(hit_point, pt_to_light_dir, pt_to_light_dist);

    // Construct a ray from hit point to current light source
    Ray shadow_ray;
    shadow_ray.origin = hit_point + eps*pt_to_light_dir;
    shadow_ray.direction = pt_to_light_dir;

    int curr_hit_id;
    double shadow_ray_t;
    Eigen::Vector3d shadow_ray_n;

    bool hasHit = first_hit(shadow_ray, eps, objects, curr_hit_id, shadow_ray_t, shadow_ray_n);
    
    // Check if blocked by another object(s) --> having shadow
    if (hasHit && shadow_ray_t < pt_to_light_dist) continue;

    // Diffuse component
    L += (objects[hit_id]->material->kd.array() * light->I.array()).matrix()
          * std::max<double>(0, n.dot(pt_to_light_dir));

    // Specular component
    Eigen::Vector3d viewing_vec = ray.direction * -1;  // flip the incoming ray 
    Eigen::Vector3d half_vec = pt_to_light_dir.normalized() + viewing_vec.normalized();
    half_vec = half_vec.normalized();

    L += (objects[hit_id]->material->ks.array() * light->I.array()).matrix()
          * std::pow(std::max<double>(0, n.dot(half_vec)), objects[hit_id]->material->phong_exponent);
  }

  return L;
  ////////////////////////////////////////////////////////////////////////////
}
