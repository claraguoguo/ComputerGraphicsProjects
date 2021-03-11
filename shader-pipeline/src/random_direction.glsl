// Generate a pseudorandom unit 3D vector
// 
// Inputs:
//   seed  3D seed
// Returns psuedorandom, unit 3D vector drawn from uniform distribution over
// the unit sphere (assuming random2 is uniform over [0,1]²).
//
// expects: random2.glsl, PI.glsl
vec3 random_direction(vec3 seed)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code 
  vec2 pt = random2(seed);

  // Reference: https://stackoverflow.com/a/5408843
  // Take advantage of sampling rule (in spherical coordinate)
  float phi = (2*M_PI) * pt.x;  // phi --> [0, 2 PI]
  float costheta = 2*pt.y - 1;  // costheta --> [-1, 1]
  float theta = acos(costheta);

  vec3 rand_dir; 
  rand_dir.x = sin(theta) * cos(phi);
  rand_dir.y = sin(theta) * sin(phi);
  rand_dir.z = cos(theta);

  return normalize(rand_dir);
  /////////////////////////////////////////////////////////////////////////////
}
