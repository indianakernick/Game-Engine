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
#include "../../3D/OpenGL/constants.hpp"

namespace Res {
  class MeshLoaderOpenGL : public Loader {
  public:
    const std::string &getName() override;
    bool canLoad(const std::string &fileExt) override;
    Handle::Ptr load(const ID &id) override;
  private:
    static void copyVerts(MeshOpenGL::Ptr, const aiScene *);
    static void copyNorms(MeshOpenGL::Ptr, const aiScene *);
    static void copyUVs(MeshOpenGL::Ptr, const aiScene *);
    static void copyElems(MeshOpenGL::Ptr, const aiScene *);
    static void copyMat(Graphics3D::Material &, const aiMaterial *, const ID &);
    static void copyMats(MeshOpenGL::Ptr, const aiScene *, const ID &);
    static void copyChannelNames(MeshOpenGL::Ptr, const aiScene *);
    using BoneIDs = std::array<GLuint, Graphics3D::MAX_BONES_PER_VERTEX>;
    using BoneWeights = std::array<GLfloat, Graphics3D::MAX_BONES_PER_VERTEX>;
    static void copyIDWeight(std::vector<BoneIDs> &,
                             std::vector<BoneWeights> &,
                             MeshOpenGL::BoneID,
                             const aiMesh *);
    static void copyIDWeights(MeshOpenGL::Ptr, const aiScene *);
    static void copyChannel(MeshOpenGL::Ptr,
                            MeshOpenGL::Channel &,
                            const aiNodeAnim *);
    static void copyAnims(MeshOpenGL::Ptr, const aiScene *);
    static void copyBone(MeshOpenGL::Bone,
                         const aiNode *,
                         const MeshOpenGL::ChannelNames &,
                         const aiScene *);
    static const aiNode *findRootBoneNode(const aiNode *,
                                          MeshOpenGL::ChannelNames &);
    static MeshOpenGL::ChannelID copyBoneNodes(MeshOpenGL::Ptr, const aiNode *);
    static void copyBones(MeshOpenGL::Ptr, const aiScene *);
    static void convertMesh(MeshOpenGL::Ptr, const aiScene *, const ID &);
  
    static Assimp::Importer importer;
    static bool importerIsInit;
    static const unsigned int importerFlags;
    static void initImporter();
  };
}

#endif

#endif
