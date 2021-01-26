#include "hue_shift.h"
#include "hsv_to_rgb.h"
#include "rgb_to_hsv.h"
#include <cmath>
#include <iostream>

void hue_shift(
  const std::vector<unsigned char> & rgb,
  const int width,
  const int height,
  const double shift,
  std::vector<unsigned char> & shifted)
{
  shifted.resize(rgb.size());
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  for (int i = 0; i < rgb.size()/3; ++i){
    double r = (double)rgb[i*3]/255;
    double g = (double)rgb[i*3 + 1]/255;
    double b = (double)rgb[i*3 + 2]/255;

    double h, s, v;
    rgb_to_hsv(r, g, b, h, s, v);

    // Apply the hue shift
    h += shift;

    // Handles hue value ranges to make sure it's inside [0, 360]
    while (h < 0) h += 360;
    h = std::fmod(h, 360);

    hsv_to_rgb(h, s, v, r, g, b);

    shifted[i*3] = r*255;
    shifted[i*3 + 1] = g*255;
    shifted[i*3 + 2] = b*255;
  }
  ////////////////////////////////////////////////////////////////////////////
}
