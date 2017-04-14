//
//  mesh loader.hpp
//  Game Engine
//
//  Created by Indi Kernick on 11/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_platform_interface_mesh_loader_hpp
#define engine_platform_interface_mesh_loader_hpp

#include <stdexcept>
#include "mesh.hpp"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>

namespace Platform {
  class MeshLoadError final : public std::runtime_error {
  public:
    MeshLoadError(const char *);
  };
  
  void setImporterProps(Assimp::Importer &);
  Mesh::Ptr loadMesh(const aiScene *, const std::string &);
}

#endif
