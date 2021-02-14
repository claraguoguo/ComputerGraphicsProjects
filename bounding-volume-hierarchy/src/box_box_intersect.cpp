#include "box_box_intersect.h"
bool box_box_intersect(
  const BoundingBox & A,
  const BoundingBox & B)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  auto is_overlapping_1d = [](std::pair<double, double> pair1, std::pair<double, double> pair2) {
    return pair1.first < pair2.second && pair2.first < pair1.second;
  };

  return is_overlapping_1d(std::make_pair(A.min_corner.x(), A.max_corner.x()),
                           std::make_pair(B.min_corner.x(), B.max_corner.x()))
         && 
         is_overlapping_1d(std::make_pair(A.min_corner.y(), A.max_corner.y()),
                           std::make_pair(B.min_corner.y(), B.max_corner.y()))
         && 
         is_overlapping_1d(std::make_pair(A.min_corner.z(), A.max_corner.z()),
                           std::make_pair(B.min_corner.z(), B.max_corner.z()));
  ////////////////////////////////////////////////////////////////////////////
}

