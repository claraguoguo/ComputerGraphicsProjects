#include "write_ppm.h"
#include <fstream>
#include <cassert>
#include <iostream>

bool write_ppm(
  const std::string & filename,
  const std::vector<unsigned char> & data,
  const int width,
  const int height,
  const int num_channels)
{
  assert(
    (num_channels == 3 || num_channels == 1) &&
    ".ppm only supports RGB or grayscale images");
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  std::ofstream myfile;
  myfile.open(filename);

  // Required PPM header info
  if (num_channels == 1) {
		myfile << "P2" << std::endl;
	}
	else if (num_channels == 3) {
		myfile << "P3" << std::endl;
	}
  myfile << width << " " << height << std::endl;
  myfile << 255 << std::endl;

  if (!myfile) std::cout << "Failed to open file: " << filename << std::endl ;

  for (int row = 0; row < height; ++row){
    for (int col = 0; col < width*num_channels; ++col){
      myfile << unsigned(data[row*width*num_channels + col]) << " ";
    }
    myfile << std::endl;
  }
  myfile.close();
  return false;
  ////////////////////////////////////////////////////////////////////////////
}
