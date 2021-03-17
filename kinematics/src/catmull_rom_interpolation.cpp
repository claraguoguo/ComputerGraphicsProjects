#include "catmull_rom_interpolation.h"
#include <Eigen/Dense>

Eigen::Vector3d catmull_rom_interpolation(
  const std::vector<std::pair<double, Eigen::Vector3d> > & keyframes,
  double t)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code
  Eigen::Vector3d interpolated_pt(0,0,0);

  // Find the 4 control points (a.k.a closest points)
  int index = 0;
  for (index = 0; index < keyframes.size(); ++index) {
    if (keyframes[index].first > t) break; 
  }

  Eigen::Vector3d P0,P1,P2,P3, A1,A2,A3, B1,B2, C;
  double t0, t1, t2, t3;

  t0 = keyframes[index - 2].first;
  P0 = keyframes[index - 2].second;

  t1 = keyframes[index - 1].first;
  P1 = keyframes[index - 1].second;

  t2 = keyframes[index].first;
  P2 = keyframes[index].second;

  t3 = keyframes[index + 1].first;
  P3 = keyframes[index + 1].second;

  // Reference: https://www.wikiwand.com/en/Centripetal_Catmull%E2%80%93Rom_spline
  A1 = (t1 - t)/(t1 - t0)*P0 + (t - t0)/(t1 - t0)*P1;
  A2 = (t2 - t)/(t2 - t1)*P1 + (t - t1)/(t2 - t1)*P2;
  A3 = (t3 - t)/(t3 - t2)*P2 + (t - t2)/(t3 - t2)*P3;

  B1 = (t2 - t)/(t2 - t0)*A1 + (t - t0)/(t2 - t0)*A2;
  B2 = (t3 - t)/(t3 - t1)*A2 + (t - t1)/(t3 - t1)*A3;

  C = (t2 - t)/(t2 - t1)*B1 + (t - t1)/(t2 - t1)*B2;

  return C;
  /////////////////////////////////////////////////////////////////////////////
}
