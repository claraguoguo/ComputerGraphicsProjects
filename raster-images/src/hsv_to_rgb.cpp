#include "hsv_to_rgb.h"
#include <cmath>
#include <iostream>

void hsv_to_rgb(
  const double h,
  const double s,
  const double v,
  double & r,
  double & g,
  double & b)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  r = 0;
  g = 0;
  b = 0;

  double c = v*s;
  double x = c*(1 - std::abs(std::fmod(h/60, 2) - 1));
  double m = v - c;

  auto assign_rgb = [&r, &g, &b](double red, double green, double blue){
    r = red;
    g = green;
    b = blue;
  };

  if (0 <= h && h < 60) assign_rgb(c, x, 0);
  else if (60 <= h && h < 120) assign_rgb(x, c, 0);
  else if (120 <= h && h < 180) assign_rgb(0, c, x);
  else if (180 <= h && h < 240) assign_rgb(0, x, c);
  else if (240 <= h && h < 300) assign_rgb(x, 0, c);
  else assign_rgb(c, 0, x);

  // std::cout << "rbg: " << r << g << b << std::endl;

  r += m;
  g += m;
  b += m;
  ////////////////////////////////////////////////////////////////////////////
}
