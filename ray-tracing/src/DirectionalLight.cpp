#include "DirectionalLight.h"
#include <limits>

void DirectionalLight::direction(
  const Eigen::Vector3d & q, Eigen::Vector3d & d, double & max_t) const
{
  ////////////////////////////////////////////////////////////////////////////
  // multiple by -1 because this->d is the direction from light toward scene
  d = -1*this->d;
  max_t = std::numeric_limits<double>::infinity();
  ////////////////////////////////////////////////////////////////////////////
}

