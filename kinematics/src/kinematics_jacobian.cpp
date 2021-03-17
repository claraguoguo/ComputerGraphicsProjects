#include "kinematics_jacobian.h"
#include "transformed_tips.h"
#include <iostream>

void kinematics_jacobian(
  const Skeleton & skeleton,
  const Eigen::VectorXi & b,
  Eigen::MatrixXd & J)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code
  J = Eigen::MatrixXd::Zero(b.size()*3, skeleton.size()*3);

  // transform the endpoints to the posed position 
  Eigen::VectorXd posed_tips = transformed_tips(skeleton, b);
  
  transformed_tips(skeleton, b) - posed_tips;

  // A very small number used for Finite Differencing 
  double h = 1e-7;

  for (int j = 0; j < skeleton.size(); ++j) {
    // j = current bone
    for (int angle = 0; angle < skeleton[0].xzx.size(); ++angle) {
      // angle = current Euler angle
      Skeleton new_skeleton = skeleton;
      new_skeleton[j].xzx[angle] += h;
      Eigen::VectorXd jacob_j_angle
         = (transformed_tips(new_skeleton, b) - posed_tips)/h;

      for (int i = 0; i < b.size(); ++i) {
        // i = current endpoint 
        for (int axis = 0; axis < 3; ++axis){
          // axis = current axis (x, y, z)
          
          // apply Finite Differencing to compute the Jacobian
          J(i*3 + axis, j*3 + angle) = jacob_j_angle[i*3 + axis];
        }
      }
    }
  }
  /////////////////////////////////////////////////////////////////////////////
}
