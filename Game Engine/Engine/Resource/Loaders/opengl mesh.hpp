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
#include "../../3D/OpenGL/attribs.hpp"

namespace Res {
  class MeshLoaderOpenGL : public Loader {
  public:
    const std::string &getName() override;
    bool canLoad(const std::string &fileExt) override;
    Handle::Ptr load(const ID &id) override;
  private:
    struct Context {
      Context(MeshOpenGL::Ptr handle, size_t groups);
    
      MeshOpenGL::Ptr handle;
      std::vector<GLuint> verts;
      std::vector<GLuint> norms;
      std::vector<GLuint> UVs;
      std::vector<GLuint> elems;
      std::vector<GLuint> boneIDWeights;
    };
  
    static void copyVerts(Context &, const aiScene *);
    static void copyNorms(Context &, const aiScene *);
    static void copyUVs(Context &, const aiScene *);
    static void copyElems(Context &, const aiScene *);
    static void copyMat(Graphics3D::Material &, const aiMaterial *, const ID &);
    static void copyMats(Context &, const aiScene *, const ID &);
    static void copyChannelNames(Context &, const aiScene *);
    struct BoneIDWeights {
      GLuint IDs[Graphics3D::MAX_BONES_PER_VERTEX] = {0};
      GLfloat weights[Graphics3D::MAX_BONES_PER_VERTEX] = {0};
    };
    static void copyIDWeight(std::vector<BoneIDWeights> &,
                             MeshOpenGL::BoneID,
                             const aiMesh *);
    static void copyIDWeights(Context &context, const aiScene *);
    static void copyChannel(Context &context,
                            MeshOpenGL::Channel &,
                            const aiNodeAnim *);
    static void copyAnims(Context &context, const aiScene *);
    static void copyBone(MeshOpenGL::Bone,
                         const aiNode *,
                         const MeshOpenGL::ChannelNames &,
                         const aiScene *);
    static const aiNode *findRootBoneNode(const aiNode *,
                                          MeshOpenGL::ChannelNames &);
    static MeshOpenGL::ChannelID copyBoneNodes(Context &, const aiNode *);
    static void copyBones(Context &, const aiScene *);
    static void buildVAOs(Context &, const aiScene *);
    static void convertMesh(MeshOpenGL::Ptr, const aiScene *, const ID &);
  
    static Assimp::Importer importer;
    static bool importerIsInit;
    static const unsigned int importerFlags;
    static void initImporter();
  };
}

#endif

#endif
