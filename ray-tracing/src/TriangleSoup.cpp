#include "TriangleSoup.h"
#include "Triangle.h"
#include "first_hit.h"
bool TriangleSoup::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  ////////////////////////////////////////////////////////////////////////////
  int triangle_id;
  bool hasHit = first_hit(ray, min_t, triangles, triangle_id, t, n);
  if (hasHit) return true;
  return false;
  ////////////////////////////////////////////////////////////////////////////
}
