//
//  opengl mesh.hpp
//  Game Engine
//
//  Created by Indi Kernick on 2/1/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_resource_descriptions_opengl_mesh_hpp
#define engine_resource_descriptions_opengl_mesh_hpp

#include "../../Application/opengl.hpp"

#ifdef __gl_h_

#include "../desc.hpp"
#include <vector>
#include <cassert>
#include <glm/vec3.hpp>
#include "../../3D/material.hpp"

namespace Resource {
  namespace Descs {
    class MeshOpenGL : public Desc {
    public:
      using Ptr = std::shared_ptr<MeshOpenGL>;
    
      MeshOpenGL(uint8_t numGroups,
                 uint8_t numMaterials,
                 const std::vector<bool> &hasUVs,
                 const std::vector<uint8_t> &matIndicies);
      ~MeshOpenGL();
    
      const std::vector<GLuint> &getVerts() const;
      const std::vector<GLuint> &getNorms() const;
      const std::vector<GLuint> &getUVs() const;
      const std::vector<bool> &getHasUVs() const;
      const std::vector<GLuint> &getElems() const;
      const std::vector<uint8_t> &getMatIndicies() const;
      Graphics3D::Material &getMaterial(uint8_t i);
    private:
      std::vector<GLuint> verts;
      std::vector<GLuint> norms;
      std::vector<GLuint> UVs;
      std::vector<bool> hasUVs;
      std::vector<GLuint> elems;
      std::vector<uint8_t> matIndicies;
      std::vector<Graphics3D::Material> materials;
    };
  }
}

#endif

#endif
