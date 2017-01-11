//
//  opengl mesh.hpp
//  Game Engine
//
//  Created by Indi Kernick on 2/1/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_resource_loaders_opengl_mesh_hpp
#define engine_resource_loaders_opengl_mesh_hpp

#ifdef USE_OPENGL

#include "../../Application/opengl.hpp"
#include "../loader.hpp"
#include "../Handles/opengl mesh.hpp"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/DefaultLogger.hpp>
#include <iostream>
#include <vector>
#include <list>

namespace Resource {
  namespace Loaders {
    class MeshOpenGL : public Loader {
    public:
      const std::string &getName() override;
      bool canLoad(const std::string &fileExt) override;
      Handle::Ptr load(const ID &id) override;
    private:
      static Assimp::Importer importer;
      static bool importerIsInit;
      static const unsigned int importerFlags;
      static void initImporter();
    };
  }
}

#endif

#endif
