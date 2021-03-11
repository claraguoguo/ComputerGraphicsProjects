// Filter an input value to perform an even smoother step. This function should
// be a quintic polynomial with improved_smooth_step(0) = 0,
// improved_smooth_step(1) = 1, and zero first _and_ second derivatives at f=0
// and f=1. "Improving Noise" [Perlin 2002].
//
// Inputs:
//   f  input value
// Returns filtered output value
float improved_smooth_step( float f)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code 
  if (f < 0) return 0;
  else if (f > 1) return 1;
  else {
    return 4*pow(f, 5) - 8*pow(f, 4) + 2*pow(f, 2) + 3*f;
  }
  return f;
  /////////////////////////////////////////////////////////////////////////////
}
vec3 improved_smooth_step( vec3 f)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code 
  f.x = improved_smooth_step(f.x);
  f.y = improved_smooth_step(f.y);
  f.z = improved_smooth_step(f.z);
  return f;
  /////////////////////////////////////////////////////////////////////////////
}
