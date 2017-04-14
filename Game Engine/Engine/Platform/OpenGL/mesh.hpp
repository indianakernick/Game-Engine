//
//  mesh.hpp
//  Game Engine
//
//  Created by Indi Kernick on 11/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_platform_opengl_mesh_hpp
#define engine_platform_opengl_mesh_hpp

#ifdef USE_OPENGL

#include "../Interface/mesh.hpp"
#include "buffer.hpp"
#include "../../3D/material.hpp"
#include "../../3D/program type.hpp"
#include "constants.hpp"

namespace Platform {
  class MeshImpl final : public Mesh {
  public:
    using Ptr = std::shared_ptr<MeshImpl>;
    using MaterialID = uint8_t;
    
    MeshImpl() = default;
    ~MeshImpl() = default;
    
    bool isAnimated() const override;
    size_t getByteSize() const override;
    
    std::vector<MaterialID> matIndicies;
    std::vector<Graphics3D::Material> materials;
    std::vector<Graphics3D::ProgType> progTypes;
    std::vector<ElemType> indiciesNum;
    
    ArrayBuffers verts;
    ArrayBuffers norms;
    ArrayBuffers uvs;
    ArrayBuffers idWeights;
    ElementBuffers elems;
    
    size_t byteSize;
  };
}

#endif

#endif
