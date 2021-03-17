#include "projected_gradient_descent.h"
#include "line_search.h"

void projected_gradient_descent(
  const std::function<double(const Eigen::VectorXd &)> & f,
  const std::function<Eigen::VectorXd(const Eigen::VectorXd &)> & grad_f,
  const std::function<void(Eigen::VectorXd &)> & proj_z,
  const int max_iters,
  Eigen::VectorXd & z)
{
  /////////////////////////////////////////////////////////////////////////////
  // Add your code here
  double MAX_STEP = 10000;
  for (int i = 0; i < max_iters; ++i) {
    // Find the gradient dE/da
    Eigen::VectorXd gradient = grad_f(z);
    // Find the step
    double step = line_search(f, proj_z, z, gradient, MAX_STEP);
    // Compute the updated z
    z = z - step*gradient;
    // Project the updated z
    proj_z(z);
  }

  /////////////////////////////////////////////////////////////////////////////
}
