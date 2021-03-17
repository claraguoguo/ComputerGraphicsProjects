#include "forward_kinematics.h"
#include "euler_angles_to_transform.h"
#include <functional> // std::function
#include "Skeleton.h"

 Eigen::Affine3d compute_trans_matrix(const Skeleton skeleton, const Bone bone) {
    if (bone.parent_index == -1) {
      // Root --> transformation is Identity matrix
      return Eigen::Affine3d::Identity();
    }
    else {
      Eigen::Affine3d parent_T = compute_trans_matrix(skeleton, skeleton[bone.parent_index]);

      // Transformation = parent_T * rest_T * rotaion * rest_T.inverse
      return parent_T*bone.rest_T*euler_angles_to_transform(bone.xzx)*bone.rest_T.inverse();
    }
 }

void forward_kinematics(
  const Skeleton & skeleton,
  std::vector<Eigen::Affine3d,Eigen::aligned_allocator<Eigen::Affine3d> > & T)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code
  T.resize(skeleton.size(),Eigen::Affine3d::Identity());
  
  for (int i = 0; i < skeleton.size(); ++i) {
    Bone bone = skeleton[i];
    T[i] = compute_trans_matrix(skeleton, bone);
  }
  /////////////////////////////////////////////////////////////////////////////
}
