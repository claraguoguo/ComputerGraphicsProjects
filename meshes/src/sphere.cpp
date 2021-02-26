#include "sphere.h"
#include <iostream>
#include <math.h>

void sphere(
  const int num_faces_u,
  const int num_faces_v,
  Eigen::MatrixXd & V,
  Eigen::MatrixXi & F,
  Eigen::MatrixXd & UV,
  Eigen::MatrixXi & UF,
  Eigen::MatrixXd & NV,
  Eigen::MatrixXi & NF)
{
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here:
  int num_faces = num_faces_u*num_faces_v;
  int num_vertices = (num_faces_v + 1)*(num_faces_u + 1);
  V.resize(num_vertices,3);
  F.resize(num_faces,4);
  UV.resize(num_vertices,2);
  UF.resize(num_faces,4);
  NV.resize(num_vertices,3);
  NF.resize(num_faces,4);

  int counter = 0; 
  double x, y, z, theta, phi, u, v;
  for (double i = 0; i < num_faces_u; ++i){
    for (double j = 0; j < num_faces_v; ++j){
      u = i/num_faces_u;
      v = j/num_faces_v;

      // Ref: Textbook P-42
      theta = v*M_PI;
      phi = u*(2*M_PI);
      x = cos(phi)*sin(theta);
      y = sin(phi)*sin(theta);
      z = cos(theta);

      V.row(counter) = Eigen::RowVector3d(x, y, z);
      UV.row(counter) = Eigen::RowVector2d(u, v);
      // For a unit sphere, normal of any point (x,y,z) is just (x,y,z)
      NV.row(counter) = Eigen::RowVector3d(x, y, z);

      counter++;
    }
  }
  
  counter = 0;  // Reset counter
  int v1, v2, v3, v4;  // 4 corners of poly
  for (double i = 0; i < num_faces_u; ++i){
    for (double j = 0; j < num_faces_v; ++j){
      v1 = j + (num_faces_v + 1)*i;
      v2 = j + (num_faces_v + 1)*(i+1);
      v3 = v2 + 1;
      v4 = v1 + 1;

      F.row(counter) = Eigen::RowVector4i(v1, v2, v3, v4);
      UF.row(counter) = Eigen::RowVector4i(v1, v2, v3, v4);
      NF.row(counter) = Eigen::RowVector4i(v1, v2, v3, v4);

      counter++;
    }
  }

  ////////////////////////////////////////////////////////////////////////////
}
