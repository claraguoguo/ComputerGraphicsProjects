#include "insert_triangle_into_box.h"

void insert_triangle_into_box(
  const Eigen::RowVector3d & a,
  const Eigen::RowVector3d & b,
  const Eigen::RowVector3d & c,
  BoundingBox & B)
{
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  double x_min = std::min(std::min(a.x(), b.x()), c.x());
  double y_min = std::min(std::min(a.y(), b.y()), c.y());
  double z_min = std::min(std::min(a.z(), b.z()), c.z());

  double x_max = std::max(std::max(a.x(), b.x()), c.x());
  double y_max = std::max(std::max(a.y(), b.y()), c.y());
  double z_max = std::max(std::max(a.z(), b.z()), c.z());

  B.min_corner.x() = std::min(x_min, B.min_corner.x());
  B.min_corner.y() = std::min(y_min, B.min_corner.y());
  B.min_corner.z() = std::min(z_min, B.min_corner.z());

  B.max_corner.x() = std::max(x_max, B.max_corner.x());
  B.max_corner.y() = std::max(y_max, B.max_corner.y());
  B.max_corner.z() = std::max(z_max, B.max_corner.z());
  ////////////////////////////////////////////////////////////////////////////
}


