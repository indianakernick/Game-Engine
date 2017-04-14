//
//  mesh.cpp
//  Game Engine
//
//  Created by Indi Kernick on 14/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "mesh.hpp"

Assimp::Importer Res::MeshLoader::importer;
bool Res::MeshLoader::importerIsInit = false;
const Res::MeshLoader::ImporterFlags Res::MeshLoader::IMPORTER_FLAGS =
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

const std::string &Res::MeshLoader::getName() const {
  static const std::string NAME = "Mesh";
  return NAME;
}

bool Res::MeshLoader::canLoad(std::experimental::string_view ext) const {
  static const char *EXTS[] = {
    "dae","blend","bvh","3ds","ase","obj","ply","dxf","ifc","nff",
    "smd","vta","md1","md2","md3","pk3","mdc","md5mesh","md5anim","md5camera",
    "x","q3o","q3s","raw","ac","stl","dxf","irrmesh","irr","off",
    "ter","mdl","hmp","ms3d","lwo","lws","lxo","csm","cob","scn"
  };
  return hasExt(EXTS, ext);
}

Res::Handle::Ptr Res::MeshLoader::load(const Res::ID &id) const {
  initImporter();
  const aiScene *scene = importer.ReadFile(absPath(id), IMPORTER_FLAGS);
  if (!scene) {
    LOG_ERROR(RESOURCES,
      "Failed to load mesh \"%s\". Assimp - %s",
      id.getPathC(), importer.GetErrorString());
    return nullptr;
  }
  
  Mesh::Ptr handle = std::make_shared<Mesh>(
    Platform::loadMesh(
      scene,
      id.getEnclosingFolder().to_string()
    )
  );
  copyChannelNames(handle, *scene);
  
  const aiNode *rootBoneNode =
    findRootBoneNode(scene->mRootNode, handle->channelNames);
  if (rootBoneNode == nullptr) {
    LOG_ERROR(RESOURCES, "Mesh has animations but the root bone was not found");
  }
  
  copyBoneNodes(handle, rootBoneNode);
  copyBones(handle, *scene);
  copyAnims(handle, *scene);
  
  return handle;
}

namespace {
  template <typename T, typename U, std::enable_if_t<(sizeof(U) > sizeof(U *)), int> = 0>
  T cast(const U &);

  template <typename T, typename U, std::enable_if_t<sizeof(U) <= sizeof(U *), int> = 0>
  T cast(const U);
  
  template <>
  glm::vec3 cast(const aiVector3D &aiVector) {
    return {aiVector.x, aiVector.y, aiVector.z};
  }

  template <>
  glm::quat cast(const aiQuaternion &aiQuat) {
    return {aiQuat.w, aiQuat.x, aiQuat.y, aiQuat.z};
  }
  
  template <>
  Res::Mesh::SubChannelKey<glm::vec3> cast(const aiVectorKey &aiKey) {
    return {
      static_cast<Res::Mesh::Time>(aiKey.mTime),
      cast<glm::vec3>(aiKey.mValue),
    };
  }

  template <>
  Res::Mesh::SubChannelKey<glm::quat> cast(const aiQuatKey &aiKey) {
    return {
      static_cast<Res::Mesh::Time>(aiKey.mTime),
      cast<glm::quat>(aiKey.mValue),
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
}

void Res::MeshLoader::copyChannelNames(Mesh::Ptr handle, const aiScene &scene) {
  if (!scene.HasAnimations()) {
    return;
  }
  /*
  Create a map of string name to channel ID. Generate a channel ID for each
  aiBone in each aiMesh. Insert the name of the aiBone with the channel ID
  into the map.
  */
  
  //reserving channel 0 for the root
  Mesh::ChannelID channelIDAccum = 1;
  
  for (size_t m = 0; m != scene.mNumMeshes; m++) {
    const aiMesh &mesh = *scene.mMeshes[m];
    for (size_t b = 0; b != mesh.mNumBones; b++) {
      const aiBone &bone = *mesh.mBones[b];
      if (handle->channelNames.emplace(bone.mName.C_Str(), channelIDAccum).second) {
        channelIDAccum++;
      }
    }
  }
  
  handle->boneNodes.resize(handle->channelNames.size() + 1);
}

void Res::MeshLoader::copyChannel(
  Mesh::Ptr handle,
  Mesh::Channel &channel,
  const aiNodeAnim &aiChannel
) {
  /*
  An aiNodeAnim corresponds to a Mesh::Channel so the members of aiNodeAnim are
  simply copied to a Mesh::Channel
  */

  channel.dummy = false;
  
  channel.translation.reserve(aiChannel.mNumPositionKeys);
  channel.rotation.reserve(aiChannel.mNumRotationKeys);
  channel.scaling.reserve(aiChannel.mNumScalingKeys);
  
  for (size_t k = 0; k != aiChannel.mNumPositionKeys; k++) {
    channel.translation.emplace_back(
      cast<Mesh::SubChannelKey<glm::vec3>>(
        aiChannel.mPositionKeys[k]
      )
    );
  }
  
  for (size_t k = 0; k != aiChannel.mNumRotationKeys; k++) {
    channel.rotation.emplace_back(
      cast<Mesh::SubChannelKey<glm::quat>>(
        aiChannel.mRotationKeys[k]
      )
    );
  }
  
  for (size_t k = 0; k != aiChannel.mNumScalingKeys; k++) {
    channel.scaling.emplace_back(
      cast<Mesh::SubChannelKey<glm::vec3>>(
        aiChannel.mScalingKeys[k]
      )
    );
  }
  
  handle->addSize(aiChannel.mNumPositionKeys * sizeof(aiVectorKey));
  handle->addSize(aiChannel.mNumRotationKeys * sizeof(aiQuatKey));
  handle->addSize(aiChannel.mNumScalingKeys * sizeof(aiVectorKey));
}

void Res::MeshLoader::copyAnims(Mesh::Ptr handle, const aiScene &scene) {
  /*
  For each aiAnimation,
    its name is placed into animNames
    some common members are copied to a Mesh::Anim
    the channels are copied to a Mesh::Channels
    For each aiNodeAnim,
      each channel has a mNodeName member which is the name of the corresponding
      aiNode. Mesh::Channels is a std::vector where the key is a Mesh::ChannelID.
      each aiNodeAnim is copied into a Mesh::Channel
  */
  
  if (!scene.HasAnimations()) {
    return;
  }
  
  handle->anims.resize(scene.mNumAnimations);
  for (size_t a = 0; a != scene.mNumAnimations; a++) {
    const aiAnimation &aiAnim = *scene.mAnimations[a];
    handle->animNames.emplace(aiAnim.mName.C_Str(), a);
    Mesh::Anim &anim = handle->anims[a];
    anim.duration = aiAnim.mDuration;
    anim.ticksPerSecond = aiAnim.mTicksPerSecond;
    anim.channels.resize(handle->channelNames.size());
    
    for (size_t c = 0; c != aiAnim.mNumChannels; c++) {
      const aiNodeAnim &aiChannel = *aiAnim.mChannels[c];
      Mesh::ChannelID channelID =
        handle->channelNames.at(aiChannel.mNodeName.C_Str());
      copyChannel(handle, anim.channels[channelID], aiChannel);
    }
    
    handle->addSize(aiAnim.mNumChannels * sizeof(Mesh::Channel));
  }
  
  handle->addSize(scene.mNumAnimations * sizeof(Mesh::Anim));
}

const aiNode *Res::MeshLoader::findRootBoneNode(
  const aiNode *root,
  Mesh::ChannelNames &channelNames
) {
  /*
  Starting at the root aiNode, traverse down the tree until a bone node is found.
  A bone node has the same name as an animation channel. The root bone node is
  the parent of the first found bone node.
  */

  auto iter = channelNames.find(root->mName.C_Str());
  if (iter == channelNames.end()) {
    for (size_t c = 0; c != root->mNumChildren; c++) {
      const aiNode *node = findRootBoneNode(root->mChildren[c], channelNames);
      if (node) {
        return node;
      }
    }
    return nullptr;
  } else {
    const aiNode *rootBoneNode = root->mParent;
    channelNames.emplace(rootBoneNode->mName.C_Str(), 0);
    return rootBoneNode;
  }
}

Res::Mesh::ChannelID Res::MeshLoader::copyBoneNodes(
  Mesh::Ptr handle,
  const aiNode *node
) {
  /*
  Starting at the root bone node traverse the tree copying the transform matrix
  of each node. Each Mesh::BoneNode is stored in a std::vector where the key is
  a Mesh::ChannelID. Each Mesh::BoneNode stores a std::vector of Mesh::ChannelID
  which are the keys of its children.
  */

  Mesh::ChannelID channel = handle->channelNames.at(node->mName.C_Str());
  Mesh::BoneNode &boneNode = handle->boneNodes[channel];
  boneNode.transform = cast<glm::mat4>(node->mTransformation);
  boneNode.children.reserve(node->mNumChildren);
  for (size_t c = 0; c != node->mNumChildren; c++) {
    boneNode.children.push_back(copyBoneNodes(handle, node->mChildren[c]));
  }
  return channel;
}

void Res::MeshLoader::copyBones(Mesh::Ptr handle, const aiScene &scene) {
  if (!scene.HasAnimations()) {
    return;
  }
  
  /*
  A Mesh::Bone corresponds to an aiBone. A Mesh::Bone stores a Mesh::ChannelID
  instead of a string which maps it to a Mesh::BoneNode and Mesh::Channel.
  */
  
  for (size_t m = 0; m != scene.mNumMeshes; m++) {
    const aiMesh &mesh = *scene.mMeshes[m];
    for (size_t b = 0; b != mesh.mNumBones; b++) {
      const aiBone &bone = *mesh.mBones[b];
      handle->bones.push_back({
        handle->channelNames.at(bone.mName.C_Str()),
        cast<glm::mat4>(bone.mOffsetMatrix)
      });
    }
  }
}

//these are purely an implementation detail so they don't need to be in
//the header

class DebugStream final : public Assimp::LogStream {
public:
  void write(const char *message) override {
    LOG_DEBUG(RESOURCES, "Assimp - %s", message);
  }
};

class InfoStream final : public Assimp::LogStream {
public:
  void write(const char *message) override {
    LOG_INFO(RESOURCES, "Assimp - %s", message);
  }
};

class WarningStream final : public Assimp::LogStream {
public:
  void write(const char *message) override {
    LOG_WARNING(RESOURCES, "Assimp - %s", message);
  }
};

class ErrorStream final : public Assimp::LogStream {
public:
  void write(const char *message) override {
    LOG_ERROR(RESOURCES, "Assimp - %s", message);
  }
};

void Res::MeshLoader::initImporter() {
  if (importerIsInit) {
    return;
  }
  
  Assimp::DefaultLogger::create(nullptr, Assimp::Logger::NORMAL, 0, nullptr);
  Assimp::Logger *logger = Assimp::DefaultLogger::get();
  logger->attachStream(new DebugStream,   Assimp::Logger::Debugging);
  logger->attachStream(new InfoStream,    Assimp::Logger::Info);
  logger->attachStream(new WarningStream, Assimp::Logger::Warn);
  logger->attachStream(new ErrorStream,   Assimp::Logger::Err);

  importer.SetPropertyFloat(
    AI_CONFIG_PP_GSN_MAX_SMOOTHING_ANGLE,
    80
  );
  importer.SetPropertyInteger(
    AI_CONFIG_PP_SBP_REMOVE,
    aiPrimitiveType_POINT |
    aiPrimitiveType_LINE
  );
  importer.SetPropertyInteger(
    AI_CONFIG_PP_RVC_FLAGS,
    aiComponent_COLORS                  |
    aiComponent_LIGHTS                  |
    aiComponent_CAMERAS                 |
    aiComponent_TEXTURES                |
    aiComponent_TANGENTS_AND_BITANGENTS
  );
  
  Platform::setImporterProps(importer);
  
  assert(importer.ValidateFlags(IMPORTER_FLAGS));
  
  importerIsInit = true;
}
