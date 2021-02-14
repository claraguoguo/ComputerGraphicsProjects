#include "point_box_squared_distance.h"

double point_box_squared_distance(
  const Eigen::RowVector3d & query,
  const BoundingBox & box)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here
  // Reference: https://stackoverflow.com/a/18157551
  double diff_x = std::max(std::max(query.x() - box.max_corner.x(), 0.0), box.min_corner.x() - query.x());
  double diff_y = std::max(std::max(query.y() - box.max_corner.y(), 0.0), box.min_corner.y() - query.y());
  double diff_z = std::max(std::max(query.z() - box.max_corner.z(), 0.0), box.min_corner.z() - query.z());
 
  return diff_x*diff_x + diff_y*diff_y + diff_z*diff_z;
  ////////////////////////////////////////////////////////////////////////////
}
