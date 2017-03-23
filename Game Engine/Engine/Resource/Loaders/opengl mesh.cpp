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

const std::string &MeshLoaderOpenGL::getName() const {
  static const std::string NAME = "OpenGL mesh";
  return NAME;
}

bool MeshLoaderOpenGL::canLoad(std::experimental::string_view ext) const {
  static const char *EXTS[] = {
    "dae","blend","bvh","3ds","ase","obj","ply","dxf","ifc","nff",
    "smd","vta","md1","md2","md3","pk3","mdc","md5mesh","md5anim","md5camera",
    "x","q3o","q3s","raw","ac","stl","dxf","irrmesh","irr","off",
    "ter","mdl","hmp","ms3d","lwo","lws","lxo","csm","cob","scn"
  };
  return hasExt(EXTS, ext);
}

MeshLoaderOpenGL::Context::Context(MeshOpenGL::Ptr handle, size_t groups)
  : handle(handle),
    verts(groups),
    norms(groups),
    UVs(groups),
    elems(groups),
    boneIDWeights(groups) {}

template <typename T, typename U, std::enable_if_t<(sizeof(U) > sizeof(U *)), int> = 0>
T cast(const U &);

template <typename T, typename U, std::enable_if_t<sizeof(U) <= sizeof(U *), int> = 0>
T cast(const U);

template <>
glm::vec3 cast(const aiColor3D &aiColor) {
  return {aiColor.r, aiColor.g, aiColor.b};
}

template <>
glm::vec4 cast(const aiColor4D &aiColor) {
  return {aiColor.r, aiColor.g, aiColor.b, aiColor.a};
}

template <>
glm::vec2 cast(const aiVector2D aiVector) {
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

template <>
Graphics3D::FragType cast(const aiShadingMode shader) {
  switch (shader) {
    case aiShadingMode_Flat:
    case aiShadingMode_Gouraud:
    case aiShadingMode_Phong:
      return Graphics3D::FragType::PHONG;
    case aiShadingMode_Blinn:
      return Graphics3D::FragType::BLINN;
    case aiShadingMode_Toon:
      return Graphics3D::FragType::TOON;
    case aiShadingMode_OrenNayar:
      return Graphics3D::FragType::OREN_NAYER;
    case aiShadingMode_Minnaert:
      return Graphics3D::FragType::MINNAERT;
    case aiShadingMode_CookTorrance:
      return Graphics3D::FragType::COOK_TORRANCE;
    case aiShadingMode_NoShading:
      return Graphics3D::FragType::SOLID;
    case aiShadingMode_Fresnel:
      return Graphics3D::FragType::FRESNEL;
    
    default:
      assert(false);
  }
}

template <>
Graphics3D::TexWrap cast(const aiTextureMapMode mapping) {
  using namespace Graphics3D;
  
  switch (mapping) {
    case aiTextureMapMode_Wrap:
      return TexWrap::REPEAT;
    case aiTextureMapMode_Clamp:
      return TexWrap::CLAMP;
    case aiTextureMapMode_Decal:
      return TexWrap::CLAMP_BORDER;
    case aiTextureMapMode_Mirror:
      return TexWrap::REPEAT_MIRROR;
    
    default:
      assert(false);
  }
}

Handle::Ptr MeshLoaderOpenGL::load(const ID &id) const {
  initImporter();
  const aiScene *scene = importer.ReadFile(absPath(id), importerFlags);
  if (!scene) {
    LOG_ERROR(RESOURCES,
      "Failed to load mesh \"%s\". Assimp - %s",
      id.getPathC(), importer.GetErrorString());
    return nullptr;
  }
  
  //references to the materials
  std::vector<uint8_t> matIndicies(scene->mNumMeshes);
  for (unsigned i = 0; i < scene->mNumMeshes; i++) {
    matIndicies[i] = scene->mMeshes[i]->mMaterialIndex;
  }
  
  MeshOpenGL::Ptr handle =
    std::make_shared<MeshOpenGL>(scene->mNumMeshes,
                                 scene->mNumMaterials,
                                 matIndicies);
  
  convertMesh(handle, scene, id);
  return handle;
}

void MeshLoaderOpenGL::copyVerts(Context &context, const aiScene *scene) {
  glGenBuffers(static_cast<GLsizei>(context.verts.size()), context.verts.data());
  for (unsigned i = 0; i < context.verts.size(); i++) {
    glBindBuffer(GL_ARRAY_BUFFER, context.verts[i]);
    glBufferData(GL_ARRAY_BUFFER,
                 scene->mMeshes[i]->mNumVertices * sizeof(aiVector3D),
                 scene->mMeshes[i]->mVertices,
                 GL_STATIC_DRAW);
    context.handle->addSize(scene->mMeshes[i]->mNumVertices * sizeof(aiVector3D));
  }
  
  CHECK_OPENGL_ERROR();
}

void MeshLoaderOpenGL::copyNorms(Context &context, const aiScene *scene) {
  glGenBuffers(static_cast<GLsizei>(context.norms.size()), context.norms.data());
  for (unsigned i = 0; i < context.norms.size(); i++) {
    glBindBuffer(GL_ARRAY_BUFFER, context.norms[i]);
    glBufferData(GL_ARRAY_BUFFER,
                 scene->mMeshes[i]->mNumVertices * sizeof(aiVector3D),
                 scene->mMeshes[i]->mNormals,
                 GL_STATIC_DRAW);
    context.handle->addSize(scene->mMeshes[i]->mNumVertices * sizeof(aiVector3D));
  }
  
  CHECK_OPENGL_ERROR();
}

void MeshLoaderOpenGL::copyUVs(Context &context, const aiScene *scene) {
  std::vector<aiVector2D> UVsCopy;
  for (unsigned i = 0; i < context.UVs.size(); i++) {
    if (scene->mMeshes[i]->HasTextureCoords(0)) {
      glGenBuffers(1, &context.UVs[i]);
      glBindBuffer(GL_ARRAY_BUFFER, context.UVs[i]);
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
      context.handle->addSize(UVsCopy.size() * sizeof(aiVector2D));
    } else {
      context.UVs[i] = 0;
    }
  }
  
  CHECK_OPENGL_ERROR();
}

void MeshLoaderOpenGL::copyElems(Context &context, const aiScene *scene) {
  glGenBuffers(static_cast<GLsizei>(context.elems.size()), context.elems.data());
  std::vector<Graphics3D::ElemType> elemsCopy;
  for (unsigned i = 0; i < context.elems.size(); i++) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, context.elems[i]);
    const aiMesh *mesh = scene->mMeshes[i];
    //there should only be triangles
    elemsCopy.resize(mesh->mNumFaces * 3);
    for (unsigned j = 0; j < mesh->mNumFaces; j++) {
      elemsCopy[j * 3 + 0] = mesh->mFaces[j].mIndices[0];
      elemsCopy[j * 3 + 1] = mesh->mFaces[j].mIndices[1];
      elemsCopy[j * 3 + 2] = mesh->mFaces[j].mIndices[2];
    }
    context.handle->indiciesNum[i] = static_cast<unsigned>(elemsCopy.size());
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 elemsCopy.size() * Graphics3D::ELEM_SIZE,
                 elemsCopy.data(),
                 GL_STATIC_DRAW);
    context.handle->addSize(elemsCopy.size() * Graphics3D::ELEM_SIZE);
  }
  
  CHECK_OPENGL_ERROR();
}

void setTexture(const aiMaterial *material,
                const std::string &folder,
                aiTextureType type,
                Res::ID &texture) {
  aiString aiPath;
  material->Get(AI_MATKEY_TEXTURE(type, 0), aiPath);
  if (aiPath.length > 0) {
    const std::string path = folder + aiPath.C_Str();
    Graphics3D::TexParams params;
    
    aiTextureMapMode mapping = aiTextureMapMode_Wrap;
    material->Get(AI_MATKEY_MAPPINGMODE_U(type, 0), mapping);
    params.wrapS = cast<Graphics3D::TexWrap>(mapping);
    
    mapping = aiTextureMapMode_Wrap;
    material->Get(AI_MATKEY_MAPPINGMODE_V(type, 0), mapping);
    params.wrapT = cast<Graphics3D::TexWrap>(mapping);
    
    aiTextureFlags flags = static_cast<aiTextureFlags>(0);
    material->Get(AI_MATKEY_TEXFLAGS(type, 0), flags);
    
    if (flags & aiTextureFlags_Invert) {
      params.invert = true;
    }
    if (flags & aiTextureFlags_UseAlpha) {
      params.hasAlpha = true;
    } else if (flags & aiTextureFlags_IgnoreAlpha) {
      params.hasAlpha = false;
    }
    
    texture = Res::ID(path, params);
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
  
  const std::string folder = id.getEnclosingFolder().to_string();
  setTexture(otherMaterial, folder, aiTextureType_DIFFUSE, material.diffuseTexture);
  setTexture(otherMaterial, folder, aiTextureType_AMBIENT, material.ambientTexture);
  setTexture(otherMaterial, folder, aiTextureType_SPECULAR, material.specularTexture);
}

void MeshLoaderOpenGL::copyMats(Context &context,
                                const aiScene *scene,
                                const ID &id) {
  for (unsigned i = 0; i < scene->mNumMaterials; i++) {
    copyMat(context.handle->materials[i], scene->mMaterials[i], id);
  }
  context.handle->addSize(scene->mNumMaterials * sizeof(Graphics3D::Material));
}

void MeshLoaderOpenGL::copyChannelNames(
  Context &context,
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
      if (context.handle->channelNames.insert({bone->mName.C_Str(), channelIDAccum}).second) {
        channelIDAccum++;
      }
    }
  }
  
  //the root bone node is not an aiBone so this function would not have
  //encountered its name. findRootBoneNode will find the first bone it
  //sees then the parent of that bone must be the root bone node
  context.handle->boneNodes.resize(context.handle->channelNames.size() + 1);
}

void MeshLoaderOpenGL::copyIDWeight(
  std::vector<BoneIDWeights> &boneIDWeights,
  MeshOpenGL::BoneID baseID,
  const aiMesh *mesh
) {
  boneIDWeights.resize(mesh->mNumVertices);
  static const BoneIDWeights ZERO = {};
  std::fill(boneIDWeights.begin(), boneIDWeights.end(), ZERO);
    
  for (unsigned int b = 0; b < mesh->mNumBones; b++) {
    const aiBone *bone = mesh->mBones[b];
    
    for (unsigned int w = 0; w < bone->mNumWeights; w++) {
      const aiVertexWeight weight = bone->mWeights[w];
      BoneIDWeights &idWeight = boneIDWeights[weight.mVertexId];
      
      unsigned int s = 0;
      while (idWeight.weights[s] != 0.0f) {
        s++;
        assert(s < Graphics3D::MAX_BONES_PER_VERTEX);
      }
      idWeight.IDs[s] = baseID + b;
      idWeight.weights[s] = weight.mWeight;
    }
  }
}

void MeshLoaderOpenGL::copyIDWeights(Context &context,
                                     const aiScene *scene) {
  if (scene->mNumAnimations == 0) {
    return;
  }
  
  std::vector<BoneIDWeights> IDWeights;
  MeshOpenGL::BoneID idAccum = 0;
  
  for (unsigned int m = 0; m < scene->mNumMeshes; m++) {
    const aiMesh *mesh = scene->mMeshes[m];
    copyIDWeight(IDWeights, idAccum, mesh);
    idAccum += mesh->mNumBones;
    
    glGenBuffers(1, &context.boneIDWeights[m]);
    glBindBuffer(GL_ARRAY_BUFFER, context.boneIDWeights[m]);
    glBufferData(GL_ARRAY_BUFFER,
                 IDWeights.size() * sizeof(BoneIDWeights),
                 IDWeights.data(),
                 GL_STATIC_DRAW);
    
    context.handle->addSize(IDWeights.size() * sizeof(BoneIDWeights));
  }
  context.handle->bones.reserve(idAccum);
  
  CHECK_OPENGL_ERROR();
}

void MeshLoaderOpenGL::copyChannel(
  Context &context,
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
  
  context.handle->addSize(aiChannel->mNumPositionKeys * sizeof(aiVectorKey));
  context.handle->addSize(aiChannel->mNumRotationKeys * sizeof(aiQuatKey));
  context.handle->addSize(aiChannel->mNumScalingKeys * sizeof(aiVectorKey));
}

void MeshLoaderOpenGL::copyAnims(
  Context &context,
  const aiScene *scene
) {
  if (scene->mNumAnimations == 0) {
    return;
  }

  context.handle->animations.resize(scene->mNumAnimations);
  for (unsigned int a = 0; a < scene->mNumAnimations; a++) {
    const aiAnimation *aiAnim = scene->mAnimations[a];
    context.handle->animNames.insert({aiAnim->mName.C_Str(), a});
    MeshOpenGL::Animation &anim = context.handle->animations[a];
    anim.duration = aiAnim->mDuration;
    anim.ticksPerSecond = aiAnim->mTicksPerSecond;
    anim.channels.resize(context.handle->channelNames.size());
    for (unsigned int c = 0; c < aiAnim->mNumChannels; c++) {
      const aiNodeAnim *aiChannel = aiAnim->mChannels[c];
      MeshOpenGL::ChannelID channelID =
        context.handle->channelNames.at(aiChannel->mNodeName.C_Str());
      copyChannel(context, anim.channels[channelID], aiChannel);
    }
    context.handle->addSize(aiAnim->mNumChannels * sizeof(MeshOpenGL::Channel));
  }
  context.handle->addSize(scene->mNumAnimations * sizeof(MeshOpenGL::Animation));
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
  Context &context,
  const aiNode *node
) {
  MeshOpenGL::ChannelID channel = context.handle->channelNames.at(node->mName.C_Str());
  MeshOpenGL::BoneNode &boneNode = context.handle->boneNodes.at(channel);
  boneNode.transform = cast<glm::mat4>(node->mTransformation);
  boneNode.children.reserve(node->mNumChildren);
  for (unsigned int i = 0; i < node->mNumChildren; i++) {
    boneNode.children.push_back(copyBoneNodes(context, node->mChildren[i]));
  }
  return channel;
}

void MeshLoaderOpenGL::copyBones(Context &context, const aiScene *scene) {
  if (scene->mNumAnimations == 0) {
    return;
  }
  
  const aiNode *rootBoneNode =
    findRootBoneNode(scene->mRootNode, context.handle->channelNames);
  if (rootBoneNode == nullptr) {
    LOG_ERROR(RESOURCES, "Mesh has animations but the root bone was not found");
    return;
  }
  
  for (unsigned int m = 0; m < scene->mNumMeshes; m++) {
    const aiMesh *mesh = scene->mMeshes[m];
    for (unsigned int b = 0; b < mesh->mNumBones; b++) {
      const aiBone *aiBone = mesh->mBones[b];
      context.handle->bones.push_back({
        context.handle->channelNames.at(aiBone->mName.C_Str()),
        static_cast<MeshOpenGL::GroupID>(m),
        cast<glm::mat4>(aiBone->mOffsetMatrix)
      });
    }
  }
  
  copyBoneNodes(context, rootBoneNode);
}

void MeshLoaderOpenGL::buildVAOs(Context &context, const aiScene *scene) {
  using namespace Graphics3D;
  
  context.handle->progTypes.resize(context.verts.size());
  context.handle->VAOs.resize(context.verts.size());
  std::vector<GLuint> &VAOs = context.handle->VAOs;
  
  for (size_t g = 0; g < context.handle->VAOs.size(); g++) {
    aiShadingMode shadingMode = aiShadingMode_Phong;
    scene->mMaterials[context.handle->matIndicies[g]]->Get(
      AI_MATKEY_SHADING_MODEL, shadingMode);
    context.handle->progTypes[g].anim = context.boneIDWeights[g];
    context.handle->progTypes[g].frag = cast<FragType>(shadingMode);
    
    glBindVertexArray(VAOs[g]);
    
    context.handle->buffers.push_back(context.verts[g]);
    glBindBuffer(GL_ARRAY_BUFFER, context.verts[g]);
    enablePos();
    posPointer(0, 0);
    
    context.handle->buffers.push_back(context.norms[g]);
    glBindBuffer(GL_ARRAY_BUFFER, context.norms[g]);
    enableNormal();
    normalPointer(0, 0);
    
    if (context.UVs[g]) {
      context.handle->buffers.push_back(context.UVs[g]);
      glBindBuffer(GL_ARRAY_BUFFER, context.UVs[g]);
      enableTexturePos();
      texturePosPointer(0, 0);
    }
    
    if (context.boneIDWeights[g]) {
      context.handle->buffers.push_back(context.boneIDWeights[g]);
      glBindBuffer(GL_ARRAY_BUFFER, context.boneIDWeights[g]);
      enableBoneID();
      enableBoneWeight();
      boneIDPointer(BONE_ID_SIZE + BONE_WGHT_SIZE, 0);
      boneWeightPointer(BONE_ID_SIZE + BONE_WGHT_SIZE, BONE_ID_SIZE);
    }
    
    context.handle->buffers.push_back(context.elems[g]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, context.elems[g]);
  }
  
  glBindVertexArray(0);
  
  CHECK_OPENGL_ERROR();
}

void MeshLoaderOpenGL::convertMesh(MeshOpenGL::Ptr handle,
                                   const aiScene *scene,
                                   const ID &id) {
  Context context(handle, scene->mNumMeshes);
  copyVerts(context, scene);
  copyNorms(context, scene);
  copyUVs(context, scene);
  copyElems(context, scene);
  copyMats(context, scene, id);
  copyChannelNames(context, scene);
  copyIDWeights(context, scene);
  copyBones(context, scene);
  copyAnims(context, scene);
  buildVAOs(context, scene);
}

//these are purely an implementation detail so they don't need to be in
//the header

class DebugStream : public Assimp::LogStream {
public:
  void write(const char *message) override {
    LOG_DEBUG(RESOURCES, "Assimp - %s", message);
  }
};

class InfoStream : public Assimp::LogStream {
public:
  void write(const char *message) override {
    LOG_INFO(RESOURCES, "Assimp - %s", message);
  }
};

class WarningStream : public Assimp::LogStream {
public:
  void write(const char *message) override {
    LOG_WARNING(RESOURCES, "Assimp - %s", message);
  }
};

class ErrorStream : public Assimp::LogStream {
public:
  void write(const char *message) override {
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
