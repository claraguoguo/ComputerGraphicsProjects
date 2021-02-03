#include <Eigen/Core>

Eigen::Vector3d reflect(const Eigen::Vector3d & in, const Eigen::Vector3d & n)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  // note: assuming vector <in> points toward the surface
  return (in - 2*n.dot(in)*n).normalized();
  ////////////////////////////////////////////////////////////////////////////
}
