#include "demosaic.h"

void demosaic(
  const std::vector<unsigned char> & bayer,
  const int & width,
  const int & height,
  std::vector<unsigned char> & rgb)
{
  rgb.resize(width*height*3);
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  for (int row = 0; row < height; ++row){
    for (int col = 0; col < width; ++col){
      double neighbor_r = 0, neighbor_g = 0, neighbor_b = 0;
      double count_r = 0, count_g = 0, count_b = 0;

      // Iterate through all 8 neighbors
      for (int dx = -1; dx < 2; ++dx){
        for (int dy = -1; dy < 2; ++dy){
          int curr_x = row + dx;
          int curr_y = col + dy;
          // Check if it goes beyond boundaries
          if (0 <= curr_x && curr_x < height && 0 <= curr_y && curr_y < width){
            if (curr_x%2 == 0){
              if (curr_y%2 == 0){
                // Green
                neighbor_g += bayer[curr_x*width + curr_y];
                count_g++;
              }
              else{
                // Blue
                neighbor_b += bayer[curr_x*width + curr_y];
                count_b++;
              }
            }
            else{
              if (curr_y%2 == 0){
                // Red
                neighbor_r += bayer[curr_x*width + curr_y];
                count_r++;
              }
              else{
                // Green
                neighbor_g += bayer[curr_x*width + curr_y];
                count_g++;
              }
            }
          }
        }
      }

      // Apply interpolation (average of neighbors) to find the missing values 
      if (row%2 == 0){
        if (col%2 == 0) { 
          rgb[row*width*3 + col*3 + 0] = neighbor_r/count_r;
          rgb[row*width*3 + col*3 + 1] = bayer[row*width + col];  // was green
          rgb[row*width*3 + col*3 + 2] = neighbor_b/count_b;
        }
        else {
          rgb[row*width*3 + col*3 + 0] = neighbor_r/count_r;
          rgb[row*width*3 + col*3 + 1] = neighbor_g/count_g;  
          rgb[row*width*3 + col*3 + 2] = bayer[row*width + col];   // was blue
        }
      }
      else {
        if (col%2 == 0){
          rgb[row*width*3 + col*3 + 0] = bayer[row*width + col];  // was red
          rgb[row*width*3 + col*3 + 1] = neighbor_g/count_g;  
          rgb[row*width*3 + col*3 + 2] = neighbor_b/count_b;
        }
        else {
          rgb[row*width*3 + col*3 + 0] = neighbor_r/count_r;
          rgb[row*width*3 + col*3 + 1] = bayer[row*width + col];  // was green
          rgb[row*width*3 + col*3 + 2] = neighbor_b/count_b;
        }
      }
    }
  }
  ////////////////////////////////////////////////////////////////////////////
}
