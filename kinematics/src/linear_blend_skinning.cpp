#include "linear_blend_skinning.h"

void linear_blend_skinning(
  const Eigen::MatrixXd & V,
  const Skeleton & skeleton,
  const std::vector<Eigen::Affine3d,Eigen::aligned_allocator<Eigen::Affine3d> > & T,
  const Eigen::MatrixXd & W,
  Eigen::MatrixXd & U)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code
  U.resize(V.rows(), V.cols());

  for (int i = 0; i < V.rows(); ++i) {
    // compute weighted average of each bone's pose transformation T[i]
    // applied to vertex's rest position
    Eigen::Vector4d weighted_sum(0,0,0,0);
    for (int j = 0; j < skeleton.size(); ++j) {
      double weight_idx = skeleton[j].weight_index;
      if (weight_idx == -1) continue;
      weighted_sum += T[j] * Eigen::Vector4d(V(i,0), V(i,1), V(i,2), 1) * W(i, weight_idx);
    }
    // normalize 
    weighted_sum /= weighted_sum[3];

    // assign weighted_sum to U
    for (int axis = 0; axis < 3; ++axis) {
      U(i, axis) = weighted_sum[axis];
    }
  }
  /////////////////////////////////////////////////////////////////////////////
}
