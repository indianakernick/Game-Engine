//
//  opengl mesh.cpp
//  Game Engine
//
//  Created by Indi Kernick on 2/1/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "opengl mesh.hpp"

#ifdef __gl_h_

using namespace Resource;

Assimp::Importer Loaders::MeshOpenGL::importer;
bool Loaders::MeshOpenGL::importerIsInit = false;
const unsigned int Loaders::MeshOpenGL::importerFlags =
  aiProcess_JoinIdenticalVertices    |
  aiProcess_Triangulate              |
  aiProcess_GenSmoothNormals         |
  aiProcess_PreTransformVertices     |
  aiProcess_ImproveCacheLocality     |
  aiProcess_RemoveRedundantMaterials |
  aiProcess_SortByPType              |
  aiProcess_FindDegenerates          |
  aiProcess_GenUVCoords              |
  aiProcess_OptimizeMeshes           |
  aiProcess_OptimizeGraph            |
  aiProcess_FlipUVs;

bool Loaders::MeshOpenGL::canLoad(const std::string &fileExt) {
  static const std::string EXT[] = {"dae","blend","bvh","3ds","ase","obj",
                                    "ply","dxf","ifc","nff","smd","vta","md1",
                                    "md2","md3","pk3","mdc","md5mesh","md5anim",
                                    "md5camera","x","q3o","q3s","raw","ac","stl",
                                    "dxf","irrmesh","irr","off","ter","mdl",
                                    "hmp","ms3d","lwo","lws","lxo","csm","cob",
                                    "scn"};
  for (const std::string &ext : EXT) {
    if (fileExt == ext) {
      return true;
    }
  }
  return false;
}

size_t Loaders::MeshOpenGL::getSize(const Memory::Buffer) {
  //mesh is stored in VRAM
  return 0;
}

bool Loaders::MeshOpenGL::useRaw() {
  return false;
}

void copyVerts(Descs::MeshOpenGL::Ptr desc, const aiScene *scene) {
  const std::vector<GLuint> &verts = desc->getVerts();
  for (unsigned i = 0; i < verts.size(); i++) {
    glBindBuffer(GL_ARRAY_BUFFER, verts[i]);
    glBufferData(GL_ARRAY_BUFFER,
                 scene->mMeshes[i]->mNumVertices * sizeof(aiVector3D),
                 scene->mMeshes[i]->mVertices,
                 GL_STATIC_DRAW);
  }
}

void copyNorms(Descs::MeshOpenGL::Ptr desc, const aiScene *scene) {
  const std::vector<GLuint> &norms = desc->getNorms();
  for (unsigned i = 0; i < norms.size(); i++) {
    glBindBuffer(GL_ARRAY_BUFFER, norms[i]);
    glBufferData(GL_ARRAY_BUFFER,
                 scene->mMeshes[i]->mNumVertices * sizeof(aiVector3D),
                 scene->mMeshes[i]->mNormals,
                 GL_STATIC_DRAW);
  }
}

void copyUVs(Descs::MeshOpenGL::Ptr desc, const aiScene *scene) {
  const std::vector<GLuint> &UVs = desc->getUVs();
  const std::vector<bool> &hasUVs = desc->getHasUVs();
  
  std::vector<aiVector2D> UVsCopy;
  for (unsigned i = 0; i < UVs.size(); i++) {
    if (hasUVs[i]) {
      glBindBuffer(GL_ARRAY_BUFFER, UVs[i]);
      //assimp stores texture coordinates as aiVector3Ds so we can't just
      //copy it directly to VRAM
      UVsCopy.resize(scene->mMeshes[i]->mNumVertices);
      for (unsigned j = 0; j < UVsCopy.size(); j++) {
        UVsCopy[j].x = scene->mMeshes[i]->mTextureCoords[0][j].x;
        UVsCopy[j].y = scene->mMeshes[i]->mTextureCoords[0][j].y;
      }
      glBufferData(GL_ARRAY_BUFFER,
                   UVsCopy.size() * sizeof(aiVector2D),
                   UVsCopy.data(),
                   GL_STATIC_DRAW);
    }
  }
}

void copyElems(Descs::MeshOpenGL::Ptr desc, const aiScene *scene) {
  const std::vector<GLuint> &elems = desc->getElems();
  
  std::vector<unsigned> elemsNum(elems.size());
  std::vector<GLushort> elemsCopy;
  for (unsigned i = 0; i < elems.size(); i++) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elems[i]);
    const aiMesh *mesh = scene->mMeshes[i];
    //there should only be triangles
    elemsCopy.resize(mesh->mNumFaces * 3);
    for (unsigned j = 0; j < mesh->mNumFaces; j++) {
      assert(mesh->mFaces[j].mNumIndices == 3);
      elemsCopy[j * 3 + 0] = mesh->mFaces[j].mIndices[0];
      elemsCopy[j * 3 + 1] = mesh->mFaces[j].mIndices[1];
      elemsCopy[j * 3 + 2] = mesh->mFaces[j].mIndices[2];
    }
    elemsNum[i] = static_cast<unsigned>(elemsCopy.size());
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 elemsCopy.size() * sizeof(GLushort),
                 elemsCopy.data(),
                 GL_STATIC_DRAW);
  }
  
  desc->setIndiciesNum(elemsNum);
}

void setBlack(aiColor4D &color) {
  color.r = 0.0f;
  color.g = 0.0f;
  color.b = 0.0f;
  color.a = 1.0f;
}

void copyMat(Graphics3D::Material &material, const aiMaterial *otherMaterial) {
  aiColor4D color;
  otherMaterial->Get(AI_MATKEY_COLOR_DIFFUSE, color);
  material.diffuse = *reinterpret_cast<Color4F *>(&color);
  
  setBlack(color);
  otherMaterial->Get(AI_MATKEY_COLOR_AMBIENT, color);
  material.ambient = *reinterpret_cast<Color4F *>(&color);
  
  setBlack(color);
  otherMaterial->Get(AI_MATKEY_COLOR_SPECULAR, color);
  material.specular = *reinterpret_cast<Color4F *>(&color);
  
  otherMaterial->Get(AI_MATKEY_SHININESS, material.shininess);
  
  aiString diffuseTexture;
  otherMaterial->Get(AI_MATKEY_TEXTURE(aiTextureType_DIFFUSE, 0), diffuseTexture);
  if (diffuseTexture.length > 0) {
    material.diffuseTexture = diffuseTexture.C_Str();
  }
}

void copyMats(Descs::MeshOpenGL::Ptr desc, const aiScene *scene) {
  for (unsigned i = 0; i < scene->mNumMaterials; i++) {
    copyMat(desc->getMaterial(i), scene->mMaterials[i]);
  }
}

void convertMesh(Descs::MeshOpenGL::Ptr desc, const aiScene *scene) {
  copyVerts(desc, scene);
  copyNorms(desc, scene);
  copyUVs(desc, scene);
  copyElems(desc, scene);
  copyMats(desc, scene);
}

Desc::Ptr Loaders::MeshOpenGL::process(const Memory::Buffer file, Memory::Buffer) {
  initImporter();
  const aiScene *scene = importer.ReadFileFromMemory(file.begin(), file.size(), importerFlags);
  if (!scene) {
    std::cerr << "Failed to load mesh: " << importer.GetErrorString() << '\n';
    return nullptr;
  }
  
  //which groups have UV channels
  std::vector<bool> hasUVs(scene->mNumMeshes);
  //references to the materials
  std::vector<uint8_t> matIndicies(scene->mNumMeshes);
  for (unsigned i = 0; i < scene->mNumMeshes; i++) {
    hasUVs[i] = scene->mMeshes[i]->HasTextureCoords(0);
    matIndicies[i] = scene->mMeshes[i]->mMaterialIndex;
  }
  
  Descs::MeshOpenGL::Ptr desc = std::make_shared<Descs::MeshOpenGL>(scene->mNumMeshes,
                                                                    scene->mNumMaterials,
                                                                    hasUVs,
                                                                    matIndicies);
  convertMesh(desc, scene);
  return desc;
}

void Loaders::MeshOpenGL::initImporter() {
  if (!importerIsInit) {
    Assimp::DefaultLogger::create();
  
    importer.SetPropertyFloat(AI_CONFIG_PP_GSN_MAX_SMOOTHING_ANGLE, 70);
    importer.SetPropertyInteger(AI_CONFIG_PP_SBP_REMOVE, aiPrimitiveType_POINT |
                                                         aiPrimitiveType_LINE);
    assert(importer.ValidateFlags(importerFlags));
    importerIsInit = true;
  }
}

#endif
