//
//  geometry3d.hpp
//  game engine
//
//  Created by Indi Kernick on 24/09/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef geometry3d_hpp
#define geometry3d_hpp

/*#include "vec3.hpp"
#include "transform3d.hpp"
#include "primview.hpp"

namespace D3 {
  class Geometry : public Transform {
  friend class Renderer;
  public:
    Geometry(int vert, int face);
    Geometry(const Buffer::View<Vec3>&, const Buffer::View<int>&);
    Geometry(const Geometry&) = default;
    Geometry(Geometry &&) = default;
    
    Geometry& operator=(const Geometry&) = default;
    Geometry& operator=(Geometry &&) = default;
    
    static Geometry makeCube();
    static Geometry makeCylinder(int = 32);
    static Geometry makeCone(int = 32);
    static Geometry makeSphere(int = 32);
  
  //private:
    Buffer::View<Vec3> verts;
    //vertsDouble points to the same memory as verts. Its like a union
    Buffer::View<double> vertsDouble;
    Buffer::View<int> faces;
  };
}*/

#endif
