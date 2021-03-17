#include "transformed_tips.h"
#include "forward_kinematics.h"

Eigen::VectorXd transformed_tips(
  const Skeleton & skeleton, 
  const Eigen::VectorXi & b)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code
  Eigen::VectorXd tips_position = Eigen::VectorXd::Zero(3 * b.size());

  std::vector<Eigen::Affine3d,Eigen::aligned_allocator<Eigen::Affine3d>> T;
  forward_kinematics(skeleton, T);

  for (int i = 0; i < b.size(); ++i) {
    int bone_idx = b[i];
    Bone bone = skeleton[bone_idx];

    /**
     *  Note: T --> maps points from rest position to posed position
     *      1. map Canonical tip to Rest tip by --> bone.rest_T * Eigen::Vector4d(bone.length, 0, 0, 1)
     *      2. x_pose = T * x_rest, where T         --> computed by forward_kinematics
     *                                    x_rest    --> rest position
     *                                    x_pose    --> posed position
    */
    Eigen::Vector4d posed_tip = T[bone_idx] * bone.rest_T * Eigen::Vector4d(bone.length, 0, 0, 1);
    // normalize
    posed_tip /= posed_tip[3];
    
    // x,y,z of rest_tip
    tips_position[i*3 + 0] = posed_tip[0];
    tips_position[i*3 + 1] = posed_tip[1];
    tips_position[i*3 + 2] = posed_tip[2];
  }

  return tips_position;

  /////////////////////////////////////////////////////////////////////////////
}
