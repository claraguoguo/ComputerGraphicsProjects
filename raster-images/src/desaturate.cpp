#include "desaturate.h"
#include "hsv_to_rgb.h"
#include "rgb_to_hsv.h"

void desaturate(
  const std::vector<unsigned char> & rgb,
  const int width,
  const int height,
  const double factor,
  std::vector<unsigned char> & desaturated)
{
  desaturated.resize(rgb.size());
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  for (int i = 0; i < rgb.size()/3; ++i){
    double r = (double)rgb[i*3]/255;
    double g = (double)rgb[i*3 + 1]/255;
    double b = (double)rgb[i*3 + 2]/255;

    double h, s, v;
    rgb_to_hsv(r, g, b, h, s, v);

    // Apply the saturation factor
    s = s*(1.0 - factor);
  
    hsv_to_rgb(h, s, v, r, g, b);

    desaturated[i*3] = r*255;
    desaturated[i*3 + 1] = g*255;
    desaturated[i*3 + 2] = b*255;
  }
  ////////////////////////////////////////////////////////////////////////////
}
