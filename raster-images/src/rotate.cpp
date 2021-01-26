#include "rotate.h"

void rotate(
  const std::vector<unsigned char> & input,
  const int width,
  const int height,
  const int num_channels,
  std::vector<unsigned char> & rotated)
{
  rotated.resize(height*width*num_channels);
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here

   // Gray-scale Image
  if (num_channels == 1){
    for (int col = 0; col < width; ++col){
      for (int row = 0; row < height; ++row){
        rotated[row + col*height] = input[row*width - col - 1];
      }
    }
  }

  else {
    for (int col = 0; col < width; ++col){
      for (int row = 0; row < height; ++row){
        // Red
        rotated[0 + row*num_channels + col*height*num_channels] = 
          input[((row + 1) * width - col)*num_channels - 3];
        // Green
        rotated[1 + row*num_channels + col*height*num_channels] = 
          input[((row + 1) * width - col)*num_channels - 2];
        // Blue
        rotated[2 + row*num_channels + col*height*num_channels] = 
          input[((row + 1) * width - col)*num_channels - 1];
      }
    }
  }
  ////////////////////////////////////////////////////////////////////////////
}
