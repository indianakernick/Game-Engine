//
//  opengl mesh.cpp
//  Game Engine
//
//  Created by Indi Kernick on 2/1/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "opengl mesh.hpp"

#ifdef USE_OPENGL

using namespace Resource;

Assimp::Importer Loaders::MeshOpenGL::importer;
bool Loaders::MeshOpenGL::importerIsInit = false;
const unsigned int Loaders::MeshOpenGL::importerFlags =
  aiProcess_JoinIdenticalVertices    |
  aiProcess_Triangulate              |
  aiProcess_GenSmoothNormals         |
  aiProcess_ImproveCacheLocality     |
  aiProcess_RemoveRedundantMaterials |
  aiProcess_SortByPType              |
  aiProcess_FindDegenerates          |
  aiProcess_GenUVCoords              |
  aiProcess_OptimizeMeshes           |
  aiProcess_OptimizeGraph            |
  aiProcess_FlipUVs;

const std::string &Loaders::MeshOpenGL::getName() {
  static const std::string NAME = "OpenGL mesh";
  return NAME;
}

bool Loaders::MeshOpenGL::canLoad(const std::string &fileExt) {
  static const std::string EXT[40] = {"dae","blend","bvh","3ds","ase","obj",
                                      "ply","dxf","ifc","nff","smd","vta","md1",
                                      "md2","md3","pk3","mdc","md5mesh","md5anim",
                                      "md5camera","x","q3o","q3s","raw","ac","stl",
                                      "dxf","irrmesh","irr","off","ter","mdl",
                                      "hmp","ms3d","lwo","lws","lxo","csm","cob",
                                      "scn"};
  return std::any_of(EXT, EXT + 40, [&fileExt](const std::string &ext) {
    return fileExt == ext;
  });
}

void copyVerts(Handles::MeshOpenGL::Ptr handle, const aiScene *scene) {
  const std::vector<GLuint> &verts = handle->getVerts();
  for (unsigned i = 0; i < verts.size(); i++) {
    glBindBuffer(GL_ARRAY_BUFFER, verts[i]);
    glBufferData(GL_ARRAY_BUFFER,
                 scene->mMeshes[i]->mNumVertices * sizeof(aiVector3D),
                 scene->mMeshes[i]->mVertices,
                 GL_STATIC_DRAW);
    handle->addSize(scene->mMeshes[i]->mNumVertices * sizeof(aiVector3D));
  }
  
  GLenum error = glGetError();
  if (error != GL_NO_ERROR) {
    LOG_ERROR(RENDERING, "Error copying vertices into mesh: %s", gluErrorString(error));
  }
}

void copyNorms(Handles::MeshOpenGL::Ptr handle, const aiScene *scene) {
  const std::vector<GLuint> &norms = handle->getNorms();
  for (unsigned i = 0; i < norms.size(); i++) {
    glBindBuffer(GL_ARRAY_BUFFER, norms[i]);
    glBufferData(GL_ARRAY_BUFFER,
                 scene->mMeshes[i]->mNumVertices * sizeof(aiVector3D),
                 scene->mMeshes[i]->mNormals,
                 GL_STATIC_DRAW);
    handle->addSize(scene->mMeshes[i]->mNumVertices * sizeof(aiVector3D));
  }
  
  GLenum error = glGetError();
  if (error != GL_NO_ERROR) {
    LOG_ERROR(RENDERING, "Error copying normals into mesh: %s", gluErrorString(error));
  }
}

void copyUVs(Handles::MeshOpenGL::Ptr handle, const aiScene *scene) {
  const std::vector<GLuint> &UVs = handle->getUVs();
  const std::vector<bool> &hasUVs = handle->getHasUVs();
  
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
      handle->addSize(UVsCopy.size() * sizeof(aiVector2D));
    }
  }
  
  GLenum error = glGetError();
  if (error != GL_NO_ERROR) {
    LOG_ERROR(RENDERING, "Error copying UVs into mesh: %s", gluErrorString(error));
  }
}

void copyElems(Handles::MeshOpenGL::Ptr handle, const aiScene *scene) {
  const std::vector<GLuint> &elems = handle->getElems();
  
  std::vector<unsigned> elemsNum(elems.size());
  std::vector<GLushort> elemsCopy;
  for (unsigned i = 0; i < elems.size(); i++) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elems[i]);
    const aiMesh *mesh = scene->mMeshes[i];
    //there should only be triangles
    elemsCopy.resize(mesh->mNumFaces * 3);
    for (unsigned j = 0; j < mesh->mNumFaces; j++) {
      elemsCopy[j * 3 + 0] = mesh->mFaces[j].mIndices[0];
      elemsCopy[j * 3 + 1] = mesh->mFaces[j].mIndices[1];
      elemsCopy[j * 3 + 2] = mesh->mFaces[j].mIndices[2];
    }
    elemsNum[i] = static_cast<unsigned>(elemsCopy.size());
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 elemsCopy.size() * sizeof(GLushort),
                 elemsCopy.data(),
                 GL_STATIC_DRAW);
    handle->addSize(elemsCopy.size() * sizeof(GLushort));
  }
  
  GLenum error = glGetError();
  if (error != GL_NO_ERROR) {
    LOG_ERROR(RENDERING, "Error copying elements into mesh: %s", gluErrorString(error));
  }
  
  handle->setIndiciesNum(elemsNum);
}

void setBlack(aiColor4D &color) {
  color.r = 0.0f;
  color.g = 0.0f;
  color.b = 0.0f;
  color.a = 1.0f;
}

void copyMat(Graphics3D::Material &material,
             const aiMaterial *otherMaterial,
             const ID &id) {
  aiColor4D color;
  otherMaterial->Get(AI_MATKEY_COLOR_DIFFUSE, color);
  material.diffuse = *reinterpret_cast<Color4F *>(&color);
  
  setBlack(color);
  otherMaterial->Get(AI_MATKEY_COLOR_AMBIENT, color);
  material.ambient = *reinterpret_cast<Color4F *>(&color);
  material.ambient = {0.2f, 0.2f, 0.2f, 0.2f};
  
  setBlack(color);
  otherMaterial->Get(AI_MATKEY_COLOR_SPECULAR, color);
  material.specular = *reinterpret_cast<Color4F *>(&color);
  ///Just to make the duck shiny
  material.specular = {1.0f, 1.0f, 1.0f, 1.0f};
  
  otherMaterial->Get(AI_MATKEY_SHININESS, material.shininess);
  material.shininess = 6;
  
  aiString diffuseTexture;
  otherMaterial->Get(AI_MATKEY_TEXTURE(aiTextureType_DIFFUSE, 0), diffuseTexture);
  if (diffuseTexture.length > 0) {
    material.diffuseTexture = id.getEnclosingFolder() + diffuseTexture.C_Str();
  }
}

void copyMats(Handles::MeshOpenGL::Ptr handle,
              const aiScene *scene,
              const ID &id) {
  for (unsigned i = 0; i < scene->mNumMaterials; i++) {
    copyMat(handle->getMaterial(i), scene->mMaterials[i], id);
  }
  handle->addSize(scene->mNumMaterials * sizeof(Graphics3D::Material));
}

void convertMesh(Handles::MeshOpenGL::Ptr handle,
                 const aiScene *scene,
                 const ID &id) {
  copyVerts(handle, scene);
  copyNorms(handle, scene);
  copyUVs(handle, scene);
  copyElems(handle, scene);
  copyMats(handle, scene, id);
}

Handle::Ptr Loaders::MeshOpenGL::load(const ID &id) {
  initImporter();
  const aiScene *scene = importer.ReadFile(absPath(id), importerFlags);
  if (!scene) {
    LOG_ERROR(RESOURCES, "Failed to load mesh \"%s\". Assimp - %s",
                         id.getPathC(), importer.GetErrorString());
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
  
  Handles::MeshOpenGL::Ptr handle =
    std::make_shared<Handles::MeshOpenGL>(scene->mNumMeshes,
                                          scene->mNumMaterials,
                                          hasUVs,
                                          matIndicies);
  convertMesh(handle, scene, id);
  return handle;
}

//these are purely an implementation detail so they don't need to be in
//the header

class DebugStream : public Assimp::LogStream {
public:
  void write(const char *message) {
    LOG_DEBUG(RESOURCES, "Assimp - %s", message);
  }
};

class InfoStream : public Assimp::LogStream {
public:
  void write(const char *message) {
    LOG_INFO(RESOURCES, "Assimp - %s", message);
  }
};

class WarningStream : public Assimp::LogStream {
public:
  void write(const char *message) {
    LOG_WARNING(RESOURCES, "Assimp - %s", message);
  }
};

class ErrorStream : public Assimp::LogStream {
public:
  void write(const char *message) {
    LOG_ERROR(RESOURCES, "Assimp - %s", message);
  }
};

void Loaders::MeshOpenGL::initImporter() {
  if (!importerIsInit) {
    Assimp::DefaultLogger::create(nullptr, Assimp::Logger::NORMAL, 0, nullptr);
    Assimp::Logger *logger = Assimp::DefaultLogger::get();
    logger->attachStream(new DebugStream, Assimp::Logger::Debugging);
    logger->attachStream(new InfoStream, Assimp::Logger::Info);
    logger->attachStream(new WarningStream, Assimp::Logger::Warn);
    logger->attachStream(new ErrorStream, Assimp::Logger::Err);
  
    importer.SetPropertyFloat(AI_CONFIG_PP_GSN_MAX_SMOOTHING_ANGLE, 70);
    importer.SetPropertyInteger(AI_CONFIG_PP_SBP_REMOVE, aiPrimitiveType_POINT |
                                                         aiPrimitiveType_LINE);
    assert(importer.ValidateFlags(importerFlags));
    importerIsInit = true;
  }
}

#endif
