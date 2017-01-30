//
//  opengl mesh.cpp
//  Game Engine
//
//  Created by Indi Kernick on 2/1/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "opengl mesh.hpp"

#ifdef USE_OPENGL

using namespace Res;

Assimp::Importer MeshLoaderOpenGL::importer;
bool MeshLoaderOpenGL::importerIsInit = false;
const unsigned int MeshLoaderOpenGL::importerFlags =
  aiProcess_JoinIdenticalVertices    |
  aiProcess_Triangulate              |
  aiProcess_GenSmoothNormals         |
  aiProcess_LimitBoneWeights         |
  aiProcess_ValidateDataStructure    |
  aiProcess_ImproveCacheLocality     |
  aiProcess_RemoveRedundantMaterials |
  aiProcess_SortByPType              |
  aiProcess_FindDegenerates          |
  aiProcess_FindInvalidData          |
  aiProcess_GenUVCoords              |
  aiProcess_TransformUVCoords        |
  aiProcess_OptimizeMeshes           |
  aiProcess_OptimizeGraph            |
  aiProcess_FlipUVs                  |
  aiProcess_RemoveComponent;

const std::string &MeshLoaderOpenGL::getName() {
  static const std::string NAME = "OpenGL mesh";
  return NAME;
}

bool MeshLoaderOpenGL::canLoad(const std::string &fileExt) {
  static const std::string EXT[40] = {
    "dae","blend","bvh","3ds","ase","obj","ply","dxf","ifc","nff","smd","vta",
    "md1","md2","md3","pk3","mdc","md5mesh","md5anim","md5camera","x","q3o",
    "q3s","raw","ac","stl","dxf","irrmesh","irr","off","ter","mdl","hmp","ms3d",
    "lwo","lws","lxo","csm","cob","scn"
  };
  return std::any_of(EXT, EXT + 40, [&fileExt](const std::string &ext) {
    return fileExt == ext;
  });
}

template <typename T, typename U>
T cast(const U &);

template <>
glm::vec3 cast(const aiColor3D &aiColor) {
  return {aiColor.r, aiColor.g, aiColor.b};
}

template <>
glm::vec4 cast(const aiColor4D &aiColor) {
  return {aiColor.r, aiColor.g, aiColor.b, aiColor.a};
}

template <>
glm::vec2 cast(const aiVector2D &aiVector) {
  return {aiVector.x, aiVector.y};
}

template <>
glm::vec3 cast(const aiVector3D &aiVector) {
  return {aiVector.x, aiVector.y, aiVector.z};
}

template <>
glm::quat cast(const aiQuaternion &aiQuat) {
  return {aiQuat.w, aiQuat.x, aiQuat.y, aiQuat.z};
}

template <>
glm::mat3 cast(const aiMatrix3x3 &aiMat) {
  //transposed
  return {
    aiMat.a1, aiMat.b1, aiMat.c1,
    aiMat.a2, aiMat.b2, aiMat.c2,
    aiMat.a3, aiMat.b3, aiMat.c3
  };
}

template <>
glm::mat4 cast(const aiMatrix4x4 &aiMat) {
  //transposed
  return {
    aiMat.a1, aiMat.b1, aiMat.c1, aiMat.d1,
    aiMat.a2, aiMat.b2, aiMat.c2, aiMat.d2,
    aiMat.a3, aiMat.b3, aiMat.c3, aiMat.d3,
    aiMat.a4, aiMat.b4, aiMat.c4, aiMat.d4
  };
}

template <>
MeshOpenGL::SubChannelKey<glm::vec3> cast(const aiVectorKey &aiKey) {
  return {
    static_cast<MeshOpenGL::Time>(aiKey.mTime),
    cast<glm::vec3>(aiKey.mValue),
  };
}

template <>
MeshOpenGL::SubChannelKey<glm::quat> cast(const aiQuatKey &aiKey) {
  return {
    static_cast<MeshOpenGL::Time>(aiKey.mTime),
    cast<glm::quat>(aiKey.mValue),
  };
}

Handle::Ptr MeshLoaderOpenGL::load(const ID &id) {
  initImporter();
  const aiScene *scene = importer.ReadFile(absPath(id), importerFlags);
  if (!scene) {
    LOG_ERROR(RESOURCES,
      "Failed to load mesh \"%s\". Assimp - %s",
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
  
  MeshOpenGL::Ptr handle =
    std::make_shared<MeshOpenGL>(scene->mNumMeshes,
                                          scene->mNumMaterials,
                                          hasUVs,
                                          matIndicies);
  
  convertMesh(handle, scene, id);
  return handle;
}

void MeshLoaderOpenGL::copyVerts(MeshOpenGL::Ptr handle, const aiScene *scene) {
  for (unsigned i = 0; i < handle->verts.size(); i++) {
    glBindBuffer(GL_ARRAY_BUFFER, handle->verts[i]);
    glBufferData(GL_ARRAY_BUFFER,
                 scene->mMeshes[i]->mNumVertices * sizeof(aiVector3D),
                 scene->mMeshes[i]->mVertices,
                 GL_STATIC_DRAW);
    handle->addSize(scene->mMeshes[i]->mNumVertices * sizeof(aiVector3D));
  }
  
  GLenum error = glGetError();
  if (error != GL_NO_ERROR) {
    LOG_ERROR(RESOURCES, "Error copying vertices into mesh: %s", gluErrorString(error));
  }
}

void MeshLoaderOpenGL::copyNorms(MeshOpenGL::Ptr handle, const aiScene *scene) {
  for (unsigned i = 0; i < handle->norms.size(); i++) {
    glBindBuffer(GL_ARRAY_BUFFER, handle->norms[i]);
    glBufferData(GL_ARRAY_BUFFER,
                 scene->mMeshes[i]->mNumVertices * sizeof(aiVector3D),
                 scene->mMeshes[i]->mNormals,
                 GL_STATIC_DRAW);
    handle->addSize(scene->mMeshes[i]->mNumVertices * sizeof(aiVector3D));
  }
  
  GLenum error = glGetError();
  if (error != GL_NO_ERROR) {
    LOG_ERROR(RESOURCES, "Error copying normals into mesh: %s", gluErrorString(error));
  }
}

void MeshLoaderOpenGL::copyUVs(MeshOpenGL::Ptr handle, const aiScene *scene) {
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
    LOG_ERROR(RESOURCES, "Error copying UVs into mesh: %s", gluErrorString(error));
  }
}

void MeshLoaderOpenGL::copyElems(MeshOpenGL::Ptr handle, const aiScene *scene) {
  const std::vector<GLuint> &elems = handle->getElems();
  
  std::vector<MeshOpenGL::ElementType> elemsCopy;
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
    handle->indiciesNum[i] = static_cast<unsigned>(elemsCopy.size());
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 elemsCopy.size() * sizeof(MeshOpenGL::ElementType),
                 elemsCopy.data(),
                 GL_STATIC_DRAW);
    handle->addSize(elemsCopy.size() * sizeof(MeshOpenGL::ElementType));
  }
  
  GLenum error = glGetError();
  if (error != GL_NO_ERROR) {
    LOG_ERROR(RESOURCES, "Error copying elements into mesh: %s", gluErrorString(error));
  }
}

void MeshLoaderOpenGL::copyMat(Graphics3D::Material &material,
             const aiMaterial *otherMaterial,
             const ID &id) {
  //When the material doesn't have a property the return value is not set
  //so the color is set to its default before getting the property
  aiColor4D color(0.5f, 0.5f, 0.5f, 1.0f);
  otherMaterial->Get(AI_MATKEY_COLOR_DIFFUSE, color);
  material.diffuse = cast<glm::vec4>(color);
  
  color = aiColor4D(0.1f, 0.1f, 0.1f, 1.0f);
  otherMaterial->Get(AI_MATKEY_COLOR_AMBIENT, color);
  material.ambient = cast<glm::vec4>(color);
  
  color = aiColor4D(1.0f, 1.0f, 1.0f, 1.0f);
  otherMaterial->Get(AI_MATKEY_COLOR_SPECULAR, color);
  material.specular = cast<glm::vec4>(color);
  
  otherMaterial->Get(AI_MATKEY_SHININESS, material.shininess);
  
  aiString diffuseTexture;
  otherMaterial->Get(AI_MATKEY_TEXTURE(aiTextureType_DIFFUSE, 0), diffuseTexture);
  if (diffuseTexture.length > 0) {
    material.diffuseTexture = id.getEnclosingFolder() + diffuseTexture.C_Str();
  }
}

void MeshLoaderOpenGL::copyMats(MeshOpenGL::Ptr handle,
                                   const aiScene *scene,
                                   const ID &id) {
  for (unsigned i = 0; i < scene->mNumMaterials; i++) {
    copyMat(handle->materials[i], scene->mMaterials[i], id);
  }
  handle->addSize(scene->mNumMaterials * sizeof(Graphics3D::Material));
}

void MeshLoaderOpenGL::copyChannelNames(
  MeshOpenGL::Ptr handle,
  const aiScene *scene
) {
  if (scene->mNumAnimations == 0) {
    return;
  }

  //reserving channel 0 for the root
  MeshOpenGL::ChannelID channelIDAccum = 1;
  
  for (unsigned int m = 0; m < scene->mNumMeshes; m++) {
    const aiMesh *mesh = scene->mMeshes[m];
    for (unsigned int b = 0; b < mesh->mNumBones; b++) {
      const aiBone *bone = mesh->mBones[b];
      if (handle->channelNames.insert({bone->mName.C_Str(), channelIDAccum}).second) {
        channelIDAccum++;
      }
    }
  }
  
  //the root bone node is not an aiBone so this function would not have
  //encountered its name. findRootBoneNode will find the first bone it
  //sees then the parent of that bone must be the root bone node
  handle->boneNodes.resize(handle->channelNames.size() + 1);
}

void MeshLoaderOpenGL::copyIDWeight(
  std::vector<BoneIDs> &boneIDs,
  std::vector<BoneWeights> &boneWeights,
  MeshOpenGL::BoneID baseID,
  const aiMesh *mesh
) {
  boneIDs.resize(mesh->mNumVertices);
  boneWeights.resize(mesh->mNumVertices);
  static const BoneIDs ZERO_IDS = {};
  static const BoneWeights ZERO_WEIGHTS = {};
  std::fill(boneIDs.begin(), boneIDs.end(), ZERO_IDS);
  std::fill(boneWeights.begin(), boneWeights.end(), ZERO_WEIGHTS);
    
  for (unsigned int b = 0; b < mesh->mNumBones; b++) {
    const aiBone *bone = mesh->mBones[b];
    
    for (unsigned int w = 0; w < bone->mNumWeights; w++) {
      const aiVertexWeight weight = bone->mWeights[w];
      BoneIDs &ids = boneIDs[weight.mVertexId];
      BoneWeights &weights = boneWeights[weight.mVertexId];
      
      unsigned int s = 0;
      while (weights[s] != 0.0f) {
        s++;
        assert(s < Graphics3D::MAX_BONES_PER_VERTEX);
      }
      ids[s] = baseID + b;
      weights[s] = weight.mWeight;
    }
  }
}

void MeshLoaderOpenGL::copyIDWeights(MeshOpenGL::Ptr handle,
                                        const aiScene *scene) {
  if (scene->mNumAnimations == 0) {
    return;
  }
  
  std::vector<BoneIDs> IDs;
  std::vector<BoneWeights> weights;
  MeshOpenGL::BoneID idAccum = 0;
  
  for (unsigned int m = 0; m < scene->mNumMeshes; m++) {
    const aiMesh *mesh = scene->mMeshes[m];
    copyIDWeight(IDs, weights, idAccum, mesh);
    idAccum += mesh->mNumBones;
    
    glGenBuffers(1, &handle->boneIDs[m]);
    glBindBuffer(GL_ARRAY_BUFFER, handle->boneIDs[m]);
    glBufferData(GL_ARRAY_BUFFER,
                 IDs.size() * sizeof(BoneIDs),
                 IDs.data(),
                 GL_STATIC_DRAW);
    
    glGenBuffers(1, &handle->boneWeights[m]);
    glBindBuffer(GL_ARRAY_BUFFER, handle->boneWeights[m]);
    glBufferData(GL_ARRAY_BUFFER,
                 weights.size() * sizeof(BoneWeights),
                 weights.data(),
                 GL_STATIC_DRAW);
    
    handle->addSize(IDs.size() * sizeof(BoneIDs));
    handle->addSize(weights.size() * sizeof(BoneWeights));
  }
  handle->bones.reserve(idAccum);
  
  GLenum error = glGetError();
  if (error != GL_NO_ERROR) {
    LOG_ERROR(RESOURCES, "Error copying bone IDs and weights into mesh: %s", gluErrorString(error));
  }
}

void MeshLoaderOpenGL::copyChannel(
  MeshOpenGL::Ptr handle,
  MeshOpenGL::Channel &channel,
  const aiNodeAnim *aiChannel
) {
  channel.dummy = false;
  
  channel.translation.reserve(aiChannel->mNumPositionKeys);
  channel.rotation.reserve(aiChannel->mNumRotationKeys);
  channel.scaling.reserve(aiChannel->mNumScalingKeys);
  
  for (unsigned int k = 0; k < aiChannel->mNumPositionKeys; k++) {
    channel.translation.emplace_back(
      cast<MeshOpenGL::SubChannelKey<glm::vec3>>(
        aiChannel->mPositionKeys[k]
      )
    );
  }
  for (unsigned int k = 0; k < aiChannel->mNumRotationKeys; k++) {
    channel.rotation.emplace_back(
      cast<MeshOpenGL::SubChannelKey<glm::quat>>(
        aiChannel->mRotationKeys[k]
      )
    );
  }
  for (unsigned int k = 0; k < aiChannel->mNumScalingKeys; k++) {
    channel.scaling.emplace_back(
      cast<MeshOpenGL::SubChannelKey<glm::vec3>>(
        aiChannel->mScalingKeys[k]
      )
    );
  }
  
  handle->addSize(aiChannel->mNumPositionKeys * sizeof(aiVectorKey));
  handle->addSize(aiChannel->mNumRotationKeys * sizeof(aiQuatKey));
  handle->addSize(aiChannel->mNumScalingKeys * sizeof(aiVectorKey));
}

void MeshLoaderOpenGL::copyAnims(
  MeshOpenGL::Ptr handle,
  const aiScene *scene
) {
  if (scene->mNumAnimations == 0) {
    return;
  }

  handle->animations.resize(scene->mNumAnimations);
  for (unsigned int a = 0; a < scene->mNumAnimations; a++) {
    const aiAnimation *aiAnim = scene->mAnimations[a];
    handle->animNames.insert({aiAnim->mName.C_Str(), a});
    MeshOpenGL::Animation &anim = handle->animations[a];
    anim.duration = aiAnim->mDuration;
    anim.ticksPerSecond = aiAnim->mTicksPerSecond;
    anim.channels.resize(handle->channelNames.size());
    for (unsigned int c = 0; c < aiAnim->mNumChannels; c++) {
      const aiNodeAnim *aiChannel = aiAnim->mChannels[c];
      MeshOpenGL::ChannelID channelID =
        handle->channelNames.at(aiChannel->mNodeName.C_Str());
      copyChannel(handle, anim.channels[channelID], aiChannel);
    }
    handle->addSize(aiAnim->mNumChannels * sizeof(MeshOpenGL::Channel));
  }
  handle->addSize(scene->mNumAnimations * sizeof(MeshOpenGL::Animation));
}

const aiNode *MeshLoaderOpenGL::findRootBoneNode(
  const aiNode *root,
  MeshOpenGL::ChannelNames &channelNames
) {
  auto iter = channelNames.find(root->mName.C_Str());
  if (iter == channelNames.end()) {
    for (unsigned int i = 0; i < root->mNumChildren; i++) {
      const aiNode *node = findRootBoneNode(root->mChildren[i], channelNames);
      if (node) {
        return node;
      }
    }
    return nullptr;
  } else {
    const aiNode *rootBoneNode = root->mParent;
    channelNames.insert({rootBoneNode->mName.C_Str(), 0});
    return rootBoneNode;
  }
}

MeshOpenGL::ChannelID MeshLoaderOpenGL::copyBoneNodes(
  MeshOpenGL::Ptr handle,
  const aiNode *node
) {
  MeshOpenGL::ChannelID channel = handle->channelNames.at(node->mName.C_Str());
  MeshOpenGL::BoneNode &boneNode = handle->boneNodes.at(channel);
  boneNode.transform = cast<glm::mat4>(node->mTransformation);
  boneNode.children.reserve(node->mNumChildren);
  for (unsigned int i = 0; i < node->mNumChildren; i++) {
    boneNode.children.push_back(copyBoneNodes(handle, node->mChildren[i]));
  }
  return channel;
}

void MeshLoaderOpenGL::copyBones(MeshOpenGL::Ptr handle, const aiScene *scene) {
  if (scene->mNumAnimations == 0) {
    return;
  }
  
  const aiNode *rootBoneNode = findRootBoneNode(scene->mRootNode, handle->channelNames);
  if (rootBoneNode == nullptr) {
    LOG_ERROR(RESOURCES, "Mesh has animations but the root bone was not found");
    return;
  }
  
  for (unsigned int m = 0; m < scene->mNumMeshes; m++) {
    const aiMesh *mesh = scene->mMeshes[m];
    for (unsigned int b = 0; b < mesh->mNumBones; b++) {
      const aiBone *aiBone = mesh->mBones[b];
      handle->bones.push_back({
        handle->channelNames.at(aiBone->mName.C_Str()),
        static_cast<MeshOpenGL::GroupID>(m),
        cast<glm::mat4>(aiBone->mOffsetMatrix)
      });
    }
  }
  
  copyBoneNodes(handle, rootBoneNode);
}

void MeshLoaderOpenGL::convertMesh(MeshOpenGL::Ptr handle,
                                      const aiScene *scene,
                                      const ID &id) {
  copyVerts(handle, scene);
  copyNorms(handle, scene);
  copyUVs(handle, scene);
  copyElems(handle, scene);
  copyMats(handle, scene, id);
  copyChannelNames(handle, scene);
  copyIDWeights(handle, scene);
  copyBones(handle, scene);
  copyAnims(handle, scene);
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

void MeshLoaderOpenGL::initImporter() {
  if (!importerIsInit) {
    Assimp::DefaultLogger::create(nullptr, Assimp::Logger::NORMAL, 0, nullptr);
    Assimp::Logger *logger = Assimp::DefaultLogger::get();
    logger->attachStream(new DebugStream, Assimp::Logger::Debugging);
    logger->attachStream(new InfoStream, Assimp::Logger::Info);
    logger->attachStream(new WarningStream, Assimp::Logger::Warn);
    logger->attachStream(new ErrorStream, Assimp::Logger::Err);
  
    importer.SetPropertyFloat(AI_CONFIG_PP_GSN_MAX_SMOOTHING_ANGLE, 80);
    importer.SetPropertyInteger(AI_CONFIG_PP_SBP_REMOVE, aiPrimitiveType_POINT |
                                                         aiPrimitiveType_LINE);
    importer.SetPropertyInteger(AI_CONFIG_PP_LBW_MAX_WEIGHTS, Graphics3D::MAX_BONES_PER_VERTEX);
    importer.SetPropertyInteger(AI_CONFIG_PP_RVC_FLAGS,
      aiComponent_COLORS                  |
      aiComponent_LIGHTS                  |
      aiComponent_CAMERAS                 |
      aiComponent_TEXTURES                |
      aiComponent_TANGENTS_AND_BITANGENTS);
    
    assert(importer.ValidateFlags(importerFlags));
    importerIsInit = true;
  }
}

#endif
