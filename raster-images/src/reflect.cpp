#include "reflect.h"

void reflect(
  const std::vector<unsigned char> & input,
  const int width,
  const int height,
  const int num_channels,
  std::vector<unsigned char> & reflected)
{
  reflected.resize(width*height*num_channels);
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here

  // Gray-scale Image
  if (num_channels == 1){
    for (int row = 0; row < height; ++row){
      for (int col = 0; col < width; ++col){
        reflected[row*width + col] = input[row*width + width - 1 - col];
      }
    }
  }

  else {
    for (int row = 0; row < height; ++row){
      for (int col = 0; col < width; ++col){
        // Red
        reflected[0 + col*num_channels + row*width*num_channels] = 
          input[row*width*num_channels + (width - col)*num_channels - 3];
        // Green
        reflected[1 + col*num_channels + row*width*num_channels] = 
          input[row*width*num_channels + (width - col)*num_channels - 2];
        // Blue
        reflected[2 + col*num_channels + row*width*num_channels] = 
          input[row*width*num_channels + (width - col)*num_channels - 1];
      }
    }
  }
  
  ////////////////////////////////////////////////////////////////////////////
}
