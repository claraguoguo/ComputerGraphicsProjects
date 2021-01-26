#include "simulate_bayer_mosaic.h"

void simulate_bayer_mosaic(
  const std::vector<unsigned char> & rgb,
  const int & width,
  const int & height,
  std::vector<unsigned char> & bayer)
{
  bayer.resize(width*height);
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  int counter = 0;
  for (int row = 0; row < height; ++row){
    for (int col = 0; col < width; ++col){
      if (row%2 == 0){
        if (col%2 == 0) { 
          // Green
          bayer[counter] = rgb[row*width*3 + col*3 + 1];
        }
        else {
          // Blue
          bayer[counter] = rgb[row*width*3 + col*3 + 2];
        }
      }
      else {
        if (col%2 == 0){
          // Red
          bayer[counter] = rgb[row*width*3 + col*3 + 0];
        }
        else {
          // Green
          bayer[counter] = rgb[row*width*3 + col*3 + 1];
        }
      }
      counter ++;
    }
  }
  ////////////////////////////////////////////////////////////////////////////
}
