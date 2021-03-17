#include "end_effectors_objective_and_gradient.h"
#include "transformed_tips.h"
#include "kinematics_jacobian.h"
#include "copy_skeleton_at.h"
#include <iostream>

void end_effectors_objective_and_gradient(
  const Skeleton & skeleton,
  const Eigen::VectorXi & b,
  const Eigen::VectorXd & xb0,
  std::function<double(const Eigen::VectorXd &)> & f,
  std::function<Eigen::VectorXd(const Eigen::VectorXd &)> & grad_f,
  std::function<void(Eigen::VectorXd &)> & proj_z)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code

  // f == Energy function 
  f = [&](const Eigen::VectorXd & A)->double
  {
    // Update skeletons with new Euler angles: A
    Skeleton skeleton_updated = copy_skeleton_at(skeleton, A);
    // Map rest tips to posed tips
    Eigen::VectorXd posed_tips = transformed_tips(skeleton_updated, b);
    
    return (posed_tips - xb0).squaredNorm();
  };

  grad_f = [&](const Eigen::VectorXd & A)->Eigen::VectorXd
  {
    // Update skeletons with new Euler angles: A
    Skeleton skeleton_updated = copy_skeleton_at(skeleton, A);
    // Map rest tips to posed tips
    Eigen::VectorXd posed_tips = transformed_tips(skeleton_updated, b);
    // Get the Jacobian matrix: J
    Eigen::MatrixXd J;
    kinematics_jacobian(skeleton_updated, b, J);
    // Get dE/dx
    auto dEdx = 2 * (posed_tips - xb0);

    return J.transpose()*dEdx; 
  };
  proj_z = [&](Eigen::VectorXd & A)
  {
    assert(skeleton.size()*3 == A.size());
    
    for (int i = 0; i < skeleton.size(); ++i) {
      Eigen::Vector3d min = skeleton[i].xzx_min;
      Eigen::Vector3d max = skeleton[i].xzx_max;
      for (int index = 0; index < 3; ++index) {
        A[i*3 + index] = std::max(min[index], std::min(max[index], A[i*3 + index]));
      }
    }
  };
  /////////////////////////////////////////////////////////////////////////////
}
