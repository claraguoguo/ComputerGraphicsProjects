#include "line_search.h"
#include <iostream>

double line_search(
  const std::function<double(const Eigen::VectorXd &)> & f,
  const std::function<void(Eigen::VectorXd &)> & proj_z,
  const Eigen::VectorXd & z,
  const Eigen::VectorXd & dz,
  const double max_step)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code
  Eigen::VectorXd z_updated = z - max_step*dz;
  proj_z(z_updated);
  double step = max_step;
  while (f(z_updated) > f(z)) {
    // decrease step by half
    step *= 0.5;
    z_updated = z - step*dz;
    proj_z(z_updated);
  }
  return step;
  /////////////////////////////////////////////////////////////////////////////
}
