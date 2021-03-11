// Input:
//   N  3D unit normal vector
// Outputs:
//   T  3D unit tangent vector
//   B  3D unit bitangent vector
void tangent(in vec3 N, out vec3 T, out vec3 B)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code 

  // Reference: https://www.ozone3d.net/tutorials/mesh_deformer_p2.php
  vec3 v1 = cross(N, vec3(0.0, 0.0, 1.0));
  vec3 v2 = cross(N, vec3(0.0, 1.0, 0.0));

  if(length(v1) > length(v2)) T = v1;
  else T = v2;

  T = normalize(T);
  B = cross(T, N);
  B = normalize(B);
  /////////////////////////////////////////////////////////////////////////////
}
