//
//  mesh.hpp
//  Game Engine
//
//  Created by Indi Kernick on 14/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_resource_loaders_mesh_hpp
#define engine_resource_loaders_mesh_hpp

#include "../loader.hpp"
#include "../Handles/mesh.hpp"
#include "../../Platform/Interface/mesh loader.hpp"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/DefaultLogger.hpp>

namespace Res {
  class MeshLoader final : public Loader {
  public:
    const std::string &getName() const override;
    bool canLoad(std::experimental::string_view) const override;
    Handle::Ptr load(const ID &) const override;
  
  private:
    static Assimp::Importer importer;
    static bool importerIsInit;
    using ImporterFlags = std::underlying_type_t<aiPostProcessSteps>;
    static const ImporterFlags IMPORTER_FLAGS;
    static void initImporter();
    
    static void copyChannelNames(Mesh::Ptr, const aiScene &);
    static void copyChannel(Mesh::Ptr, Mesh::Channel &, const aiNodeAnim &);
    static void copyAnims(Mesh::Ptr, const aiScene &);
    static const aiNode *findRootBoneNode(const aiNode *, Mesh::ChannelNames &);
    static Mesh::ChannelID copyBoneNodes(Mesh::Ptr, const aiNode *);
    static void copyBones(Mesh::Ptr, const aiScene &);
  };
}

#endif
