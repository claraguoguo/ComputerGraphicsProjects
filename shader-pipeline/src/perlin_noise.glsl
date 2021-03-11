// Given a 3d position as a seed, compute a smooth procedural noise
// value: "Perlin Noise", also known as "Gradient noise".
//
// Inputs:
//   st  3D seed
// Returns a smooth value between (-1,1)
//
// expects: random_direction, smooth_step
float perlin_noise(vec3 st) 
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code 
  // Reference: https://en.wikipedia.org/wiki/Perlin_noise

  vec3 min = floor(st);
  vec3 max = ceil(st);
  // 8 vertices of the cube 
  vec3 v1 = min;
  vec3 v2 = vec3(max.x, min.yz);
  vec3 v3 = vec3(max.x, min.y, max.z);
  vec3 v4 = vec3(min.x, min.y, max.z);
  vec3 v5 = vec3(min.x, max.y, min.z);
  vec3 v6 = vec3(max.xy, min.z);
  vec3 v7 = max;
  vec3 v8 = vec3(min.x, max.yz);

  // random gradient vector at each vertex
  vec3 grad1 = random_direction(v1);
  vec3 grad2 = random_direction(v2);
  vec3 grad3 = random_direction(v3);
  vec3 grad4 = random_direction(v4);
  vec3 grad5 = random_direction(v5);
  vec3 grad6 = random_direction(v6);
  vec3 grad7 = random_direction(v7);
  vec3 grad8 = random_direction(v8);

  // distance vectors from st to vertices
  vec3 dist1 = st - v1;
  vec3 dist2 = st - v2;
  vec3 dist3 = st - v3;
  vec3 dist4 = st - v4;
  vec3 dist5 = st - v5;
  vec3 dist6 = st - v6;
  vec3 dist7 = st - v7;
  vec3 dist8 = st - v8;

  // compute dot product of distance vector and gradient vector for each vertex
  float prod1 = dot(dist1, grad1); 
  float prod2 = dot(dist2, grad2);
  float prod3 = dot(dist3, grad3);
  float prod4 = dot(dist4, grad4);
  float prod5 = dot(dist5, grad5);
  float prod6 = dot(dist6, grad6);
  float prod7 = dot(dist7, grad7);
  float prod8 = dot(dist8, grad8);

  // interpolation
  vec3 w = smooth_step(st - floor(st));   // interpolate weight
  float fix_1 = mix(
    mix(prod1, prod2, w.x),
    mix(prod5, prod6, w.x),
    w.y);
  float fix_2 = mix(
    mix(prod4, prod3, w.x),
    mix(prod8, prod7, w.x),
    w.y);
  
  float fix_all = mix (fix_1, fix_2, w.z);

  // scale fix_all to range [-1, 1]
  fix_all = fix_all/sqrt(3.0); 

  return fix_all;
  /////////////////////////////////////////////////////////////////////////////
}

