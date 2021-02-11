#include "ray_intersect_triangle_mesh_brute_force.h"
#include "ray_intersect_triangle.h"

bool ray_intersect_triangle_mesh_brute_force(
  const Ray & ray,
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  const double min_t,
  const double max_t,
  double & hit_t,
  int & hit_f)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  hit_t = 0;
  hit_f = 0;
  Eigen::RowVector3d curr_A, curr_B, curr_C;
  double curr_t; 

  double min_hit_t = std::numeric_limits<double>::infinity();;
  int min_hit_f = -1;
  for (int i = 0; i < F.rows(); ++i) {
    // Get the vertices of current triangle
    curr_A = V.row(F(i, 0));
    curr_B = V.row(F(i, 1));
    curr_C = V.row(F(i, 2));

    bool has_hit = ray_intersect_triangle(ray, curr_A, curr_B, curr_C, min_t, max_t, curr_t);
    if (has_hit) {
      if (curr_t < min_hit_t) {
        min_hit_t = curr_t;
        min_hit_f = i;
      }
    }
  }
  if (min_hit_f == -1) return false;

  hit_t = min_hit_t;
  hit_f = min_hit_f;
  return true;
  ////////////////////////////////////////////////////////////////////////////
}
