//
//  triangulate.hpp
//  Game Engine
//
//  Created by Indi Kernick on 31/10/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_3d_triangulate_hpp
#define engine_3d_triangulate_hpp

#include <cstdint>

namespace Triangulate {
  ///Triangulates a variable size polygon mesh
  uint32_t mesh(uint32_t *polyI, uint32_t *polySize, uint32_t polyNum, uint32_t *triI);
  ///Triangulates a fixed size polygon mesh
  uint32_t mesh(uint32_t *polyI, uint32_t  polySize, uint32_t polyNum, uint32_t *triI);
  ///Triangulates a polygon
  uint32_t poly(uint32_t *polyI, uint32_t  polySize,                   uint32_t *triI);
  ///Triangulates the indices of a polygon. Equivilent to calling
  ///poly(uint32_t *polyI, uint32_t polySize, uint32_t *triI) with polyI pointing to
  ///0,1,2,3,4...
  uint32_t poly(                 uint32_t  polySize,                   uint32_t *triI);
  
  ///Its where the magic happens!
  inline uint32_t magic(uint32_t polySize, uint32_t triIndex) {
    //i came up with this after 15min with a whiteboard
    //im quite proud of it
    return (((triIndex - triIndex / 3) % polySize    ) *
            ((triIndex - triIndex / 3) / polySize + 1)) % polySize;
  }
  
  ///Count the number of triangles resulting from triangulating the
  ///variable size polygon mesh
  uint32_t meshTriCount(uint32_t *polySize, uint32_t polyNum);
  ///Count the number of triangles resulting from triangulating the
  ///fixed size polygon mesh
  constexpr uint32_t meshTriCount(uint32_t polySize, uint32_t polyNum) {
    return (polySize - 2) * polyNum;
  }
  ///Count the number of triangles resulting from triangulation the polygon
  constexpr uint32_t polyTriCount(uint32_t polySize) {
    return polySize - 2;
  }
  
  ///Count the number of vertices resulting from triangulatin the
  ///variable size polygon mesh
  uint32_t meshVertCount(uint32_t *polySize, uint32_t polyNum);
  ///Count the number of vertices resulting from triangulating the
  ///fixed size polygon mesh
  constexpr uint32_t meshVertCount(uint32_t polySize, uint32_t polyNum) {
    return (polySize - 2) * polyNum * 3;
  }
  ///Count the number of vertices resulting from triangulation the polygon
  constexpr uint32_t polyVertCount(uint32_t polySize) {
    return (polySize - 2) * 3;
  }
}

#endif
