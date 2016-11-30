//
//  triangulate.hpp
//  Game Engine
//
//  Created by Indi Kernick on 31/10/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_3d_triangulate_hpp
#define engine_3d_triangulate_hpp

namespace Triangulate {
  using uint = unsigned int;
  ///Triangulates a variable size polygon mesh
  uint mesh(uint *polyI, uint *polySize, uint polyNum, uint *triI);
  ///Triangulates a fixed size polygon mesh
  uint mesh(uint *polyI, uint  polySize, uint polyNum, uint *triI);
  ///Triangulates a polygon
  uint poly(uint *polyI, uint  polySize,               uint *triI);
  ///Triangulates the indices of a polygon. Equivilent to calling
  ///poly(uint *polyI, uint polySize, uint *triI) with polyI pointing to
  ///0,1,2,3,4...
  uint poly(             uint  polySize,               uint *triI);
  
  ///Its where the magic happens!
  inline uint magic(uint polySize, uint triIndex) {
    //i came up with this after 15min with a whiteboard
    //im quite proud of it
    return (((triIndex - triIndex / 3) % polySize    ) *
            ((triIndex - triIndex / 3) / polySize + 1)) % polySize;
  }
  
  ///Count the number of triangles resulting from triangulating the
  ///variable size polygon mesh
  uint meshTriCount(uint *polySize, uint polyNum);
  ///Count the number of triangles resulting from triangulating the
  ///fixed size polygon mesh
  constexpr uint meshTriCount(uint polySize, uint polyNum) {
    return (polySize - 2) * polyNum;
  }
  ///Count the number of triangles resulting from triangulation the polygon
  constexpr uint polyTriCount(uint polySize) {
    return polySize - 2;
  }
  
  ///Count the number of vertices resulting from triangulatin the
  ///variable size polygon mesh
  uint meshVertCount(uint *polySize, uint polyNum);
  ///Count the number of vertices resulting from triangulating the
  ///fixed size polygon mesh
  constexpr uint meshVertCount(uint polySize, uint polyNum) {
    return (polySize - 2) * polyNum * 3;
  }
  ///Count the number of vertices resulting from triangulation the polygon
  constexpr uint polyVertCount(uint polySize) {
    return (polySize - 2) * 3;
  }
}

#endif
