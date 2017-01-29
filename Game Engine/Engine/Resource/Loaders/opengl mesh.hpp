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
#include <array>

namespace Resource {
  namespace Loaders {
    class MeshOpenGL : public Loader {
    public:
      static const unsigned int MAX_BONES_PER_VERTEX = 4;
    
      const std::string &getName() override;
      bool canLoad(const std::string &fileExt) override;
      Handle::Ptr load(const ID &id) override;
    private:
      static void copyVerts(Handles::MeshOpenGL::Ptr, const aiScene *);
      static void copyNorms(Handles::MeshOpenGL::Ptr, const aiScene *);
      static void copyUVs(Handles::MeshOpenGL::Ptr, const aiScene *);
      static void copyElems(Handles::MeshOpenGL::Ptr, const aiScene *);
      static void copyMat(Graphics3D::Material &, const aiMaterial *, const ID &);
      static void copyMats(Handles::MeshOpenGL::Ptr, const aiScene *, const ID &);
      static void copyChannelNames(Handles::MeshOpenGL::Ptr, const aiScene *);
      using BoneIDs = std::array<GLuint, MAX_BONES_PER_VERTEX>;
      using BoneWeights = std::array<GLfloat, MAX_BONES_PER_VERTEX>;
      static void copyIDWeight(std::vector<BoneIDs> &,
                               std::vector<BoneWeights> &,
                               Handles::MeshOpenGL::BoneID,
                               const aiMesh *);
      static void copyIDWeights(Handles::MeshOpenGL::Ptr, const aiScene *);
      static void copyChannel(Handles::MeshOpenGL::Ptr,
                              Handles::MeshOpenGL::Channel &,
                              const aiNodeAnim *);
      static void copyAnims(Handles::MeshOpenGL::Ptr, const aiScene *);
      static void copyBone(Handles::MeshOpenGL::Bone,
                           const aiNode *,
                           const Handles::MeshOpenGL::ChannelNames &,
                           const aiScene *);
      static const aiNode *findRootBoneNode(const aiNode *,
                                            Handles::MeshOpenGL::ChannelNames &);
      static Handles::MeshOpenGL::ChannelID copyBoneNodes(Handles::MeshOpenGL::Ptr, const aiNode *);
      static void copyBones(Handles::MeshOpenGL::Ptr, const aiScene *);
      static void convertMesh(Handles::MeshOpenGL::Ptr, const aiScene *, const ID &);
    
      static Assimp::Importer importer;
      static bool importerIsInit;
      static const unsigned int importerFlags;
      static void initImporter();
    };
  }
}

#endif

#endif
