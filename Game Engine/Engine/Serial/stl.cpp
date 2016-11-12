//
//  stl.cpp
//  game engine
//
//  Created by Indi Kernick on 2/11/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "stl.hpp"

std::vector<STL::Triangle> &STL::getTriangles() {
  return triangles;
}

void STL::write(std::ofstream &file) {
  //i found out that there isn't actually a standard for what the 80 byte header
  //should contain so i decided that this was pretty reasonable
  file.write("This is the 80 character header than must begin every STL file for some reason.\n", 80);
  uint32_t trianglesNum = static_cast<uint32_t>(triangles.size());
  file.write(reinterpret_cast<char *>(&trianglesNum), 4);
  file.write(reinterpret_cast<char *>(triangles.data()), triangles.size() * sizeof(Triangle));
}

STL STL::read(std::ifstream &file) {
  STL out;
  file.seekg(80);
  uint32_t size;
  file.read(reinterpret_cast<char *>(&size), 4);
  out.triangles.reserve(size);
  file.read(reinterpret_cast<char *>(out.triangles.data()), size * sizeof(Triangle));
  return out;
}