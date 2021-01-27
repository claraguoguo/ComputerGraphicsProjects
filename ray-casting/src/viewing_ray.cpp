#include "viewing_ray.h"

void viewing_ray(
  const Camera & camera,
  const int i,
  const int j,
  const int width,
  const int height,
  Ray & ray)
{
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  ray.origin = camera.e;

  // Note: camera plane origin is at top-left corner
  double u = camera.width/width*(j+0.5) - camera.width/2;
  double v = -1*camera.height/height*(i+0.5) + camera.height/2;

  ray.direction = u*camera.u + v*camera.v - camera.d*camera.w;
  ////////////////////////////////////////////////////////////////////////////
}

