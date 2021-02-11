#include "insert_box_into_box.h"

void insert_box_into_box(
  const BoundingBox & A,
  BoundingBox & B)
{
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  B.min_corner.x() = std::min(A.min_corner.x(), B.min_corner.x());
  B.min_corner.y() = std::min(A.min_corner.y(), B.min_corner.y());
  B.min_corner.z() = std::min(A.min_corner.z(), B.min_corner.z());

  B.max_corner.x() = std::max(A.max_corner.x(), B.max_corner.x());
  B.max_corner.y() = std::max(A.max_corner.y(), B.max_corner.y());
  B.max_corner.z() = std::max(A.max_corner.z(), B.max_corner.z());
  ////////////////////////////////////////////////////////////////////////////
}

