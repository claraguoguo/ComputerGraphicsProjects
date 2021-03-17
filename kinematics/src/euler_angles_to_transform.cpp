#include "euler_angles_to_transform.h"

Eigen::Affine3d euler_angles_to_transform(
  const Eigen::Vector3d & xzx)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code
  
  // cos() and sin() are expecting angles in radians
  // Converts from degrees to radians
  double angle1_x, angle2_z, angle3_x; 
  angle1_x = xzx[0]*M_PI/180.0;
  angle2_z = xzx[1]*M_PI/180.0;
  angle3_x = xzx[2]*M_PI/180.0;
  
  Eigen::Affine3d R1, R2, R3;

  // Rotation around x-axis
  R1.matrix() << 
    1,0,0,0,
    0,cos(angle1_x),-1*sin(angle1_x),0,
    0,sin(angle1_x),cos(angle1_x),0,
    0,0,0,1;

  // Rotation around z-axis
  R2.matrix() << 
    cos(angle2_z),-1*sin(angle2_z),0,0,
    sin(angle2_z),cos(angle2_z),0,0,
    0,0,1,0,
    0,0,0,1;

   // Rotation around x-axis
  R3.matrix() << 
    1,0,0,0,
    0,cos(angle3_x),-1*sin(angle3_x),0,
    0,sin(angle3_x),cos(angle3_x),0,
    0,0,0,1;
  
  return R3*R2*R1;
  /////////////////////////////////////////////////////////////////////////////
}
