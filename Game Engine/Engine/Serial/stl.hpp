//
//  stl.hpp
//  Game Engine
//
//  Created by Indi Kernick on 2/11/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef stl_hpp
#define stl_hpp

#include <fstream>
#include <cstdint>
#include <vector>

class STL {
public:

#pragma pack(1)
  struct Vertex {
    float x;
    float y;
    float z;
  };
  struct Triangle {
    Vertex normal;
    Vertex vertices[3];
    uint16_t attrByteCount = 0;
  };
#pragma pack()
  
  STL() = default;
  ~STL() = default;
  
  std::vector<Triangle> &getTriangles();
  
  void write(std::ofstream &);
  static STL read(std::ifstream &);
private:
  std::vector<Triangle> triangles;
};

#endif
