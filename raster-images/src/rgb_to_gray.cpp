#include "rgb_to_gray.h"

void rgb_to_gray(
  const std::vector<unsigned char> & rgb,
  const int width,
  const int height,
  std::vector<unsigned char> & gray)
{
  gray.resize(height*width);
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  auto compute_gray_value = [](float r, float g, float b) {
      return 0.2126*r + 0.7152*g + 0.0722*b;
  };

  for (int row = 0; row < height; ++row){
      for (int col = 0; col < width; ++col){
        float curr_r = rgb[row*width*3 + col*3 + 0];
        float curr_g = rgb[row*width*3 + col*3 + 1];
        float curr_b = rgb[row*width*3 + col*3 + 2];
        gray[row*width + col] = compute_gray_value(curr_r, curr_g, curr_b);
      }
  }
  ////////////////////////////////////////////////////////////////////////////
}
