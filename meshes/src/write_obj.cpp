#include "write_obj.h"
#include <fstream>
#include <cassert>
#include <iostream>

bool write_obj(
  const std::string & filename,
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  const Eigen::MatrixXd & UV,
  const Eigen::MatrixXi & UF,
  const Eigen::MatrixXd & NV,
  const Eigen::MatrixXi & NF)
{
  assert((F.size() == 0 || F.cols() == 3 || F.cols() == 4) && "F must have 3 or 4 columns");
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here:
  std::ofstream newFile;
  std::string space = " ";

  newFile.open(filename, std::ios::binary);

  // v (vertext coordinate)
  for (int i = 0; i < V.rows(); ++i) {
    newFile << "v" + space << V(i, 0) << space << V(i, 1) << space << V(i, 2) << "\n";
  }

  // f (facet vertex index/uv position/vertex normal)
  for (int i = 0; i < F.rows(); ++i) {
    newFile << "f" + space;
    for (int j = 0; j < F.cols(); ++j) {
      // .obj file index starts at 1, so need to +1
      newFile << F(i,j) + 1 << "/" 
              << UF(i,j) + 1 << "/"
              << NF(i,j) + 1 << space;
    }
    newFile << "\n";
  }
  
  // vn (normal vector)
  for (int i = 0; i < NV.rows(); ++i) {
    newFile << "vn" + space << NV(i, 0) << space << NV(i, 1) << space << NV(i, 2) << "\n";;
  }

  // vt (uv coordinate)
  for (int i = 0; i < UV.rows(); ++i) {
    newFile << "vt" + space << UV(i, 0) << space << UV(i, 1) << "\n";;
  }

  if (newFile.good()) return true;

  std::cout << "Error! Writing " + filename + " has failed!";
  ////////////////////////////////////////////////////////////////////////////
  return false;
}
