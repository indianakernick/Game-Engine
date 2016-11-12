//
//  mesh.hpp
//  game engine
//
//  Created by Indi Kernick on 6/09/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef mesh_hpp
#define mesh_hpp

#include <cstdint>
#include <vector>

namespace D3 {
#pragma pack(1)
  struct Pos {
    float x;
    float y;
    float z;
  };
  using Normal = Pos;
  struct TexturePos {
    float s;
    float t;
  };
  struct Color {
    float r;
    float g;
    float b;
  };
  struct Vertex {
    Pos pos;
    Normal normal;
    TexturePos texturePos;
    Color color;
  };
  
  struct Face {
    uint16_t a;
    uint16_t b;
    uint16_t c;
  };
#pragma pack()
  
  class Mesh {
  public:
    
  private:
    std::vector<Vertex> verts;
  };
}

#endif