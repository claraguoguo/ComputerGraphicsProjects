#include "PointLight.h"

void PointLight::direction(
  const Eigen::Vector3d & q, Eigen::Vector3d & d, double & max_t) const
{
  ////////////////////////////////////////////////////////////////////////////
  // d: query point(p) towards the light(q)
  Eigen::Vector3d dir = p - q;

  max_t = dir.norm();
  d = dir.normalized();
  ////////////////////////////////////////////////////////////////////////////
}
