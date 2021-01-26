#include "over.h"

void over(
  const std::vector<unsigned char> & A,
  const std::vector<unsigned char> & B,
  const int & width,
  const int & height,
  std::vector<unsigned char> & C)
{
  C.resize(A.size());
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  for (int i = 0; i < width * height; ++i){
    double A_r = (double)A[i*4 + 0];
    double A_g = (double)A[i*4 + 1];
    double A_b = (double)A[i*4 + 2];
    double A_a = (double)A[i*4 + 3]/255;

    double B_r = (double)B[i*4 + 0];
    double B_g = (double)B[i*4 + 1];
    double B_b = (double)B[i*4 + 2];
    double B_a = (double)B[i*4 + 3]/255;

    double C_a = (1 - A_a)*B_a + A_a;
    double C_r = (A_r*A_a + B_r*B_a*(1-A_a))/C_a;
    double C_g = (A_g*A_a + B_g*B_a*(1-A_a))/C_a;
    double C_b = (A_b*A_a + B_b*B_a*(1-A_a))/C_a;

    C[i*4 + 0] = C_r;
    C[i*4 + 1] = C_g;
    C[i*4 + 2] = C_b;
    C[i*4 + 3] = C_a * 255;
  }
  ////////////////////////////////////////////////////////////////////////////
}
