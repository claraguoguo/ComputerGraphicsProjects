#include "rgb_to_hsv.h"
#include <cmath>
#include <iostream>

void rgb_to_hsv(
  const double r,
  const double g,
  const double b,
  double & h,
  double & s,
  double & v)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  h = 0;
  s = 0;
  v = 0;

  double cmax = std::max(std::max(r, g), b);
  double cmin = std::min(std::min(r, g), b);
  double cdiff = cmax - cmin;

  // Hue
  if (cdiff == 0) h = 0;
  else if (cmax == r) h = 60*((g - b)/cdiff + 0);
  else if (cmax == g) h = 60*((b - r)/cdiff + 2);
  else h = 60*((r - g)/cdiff + 4);
  
  // Saturation
  if (cmax == 0) s = 0;
  else s = cdiff/cmax;

  // Value
  v = cmax;
  ////////////////////////////////////////////////////////////////////////////
}
