#include "rgba_to_rgb.h"

void rgba_to_rgb(
  const std::vector<unsigned char> & rgba,
  const int & width,
  const int & height,
  std::vector<unsigned char> & rgb)
{
  rgb.resize(height*width*3);

  ////////////////////////////////////////////////////////////////////////////
  int total_pixels = width*height;

  for (int i = 0; i < total_pixels; ++i) {
    // Red
    rgb[0 + i*3] = rgba[0 + i*4];
    // Green
    rgb[1 + i*3] = rgba[1 + i*4];
    // Blue
    rgb[2 + i*3] = rgba[2 + i*4];
  }
  ////////////////////////////////////////////////////////////////////////////
}
