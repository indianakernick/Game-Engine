//
//  mesh loader.cpp
//  Game Engine
//
//  Created by Indi Kernick on 11/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "mesh loader.hpp"

#ifdef USE_OPENGL

using namespace Platform;

namespace {
  ArrayBuffers copyVerts(size_t numGroups, const aiScene *scene, size_t &size) {
    static_assert(sizeof(aiVector3D) == POS_SIZE);
    assert(numGroups);
    
    ArrayBuffers verts(numGroups);
    
    for (size_t g = 0; g != numGroups; g++) {
      verts.bind(g);
      glBufferData(
        GL_ARRAY_BUFFER,
        scene->mMeshes[g]->mNumVertices * sizeof(aiVector3D),
        scene->mMeshes[g]->mVertices,
        GL_STATIC_DRAW
      );
      size += scene->mMeshes[g]->mNumVertices * sizeof(aiVector3D);
    }
    
    CHECK_OPENGL_ERROR();
    
    return verts;
  }
  
  ArrayBuffers copyNorms(size_t numGroups, const aiScene *scene, size_t &size) {
    static_assert(sizeof(aiVector3D) == NORM_SIZE);
    assert(numGroups);
    
    ArrayBuffers norms(numGroups);
    
    for (size_t g = 0; g != numGroups; g++) {
      norms.bind(g);
      glBufferData(
        GL_ARRAY_BUFFER,
        scene->mMeshes[g]->mNumVertices * sizeof(aiVector3D),
        scene->mMeshes[g]->mNormals,
        GL_STATIC_DRAW
      );
      size += scene->mMeshes[g]->mNumVertices * sizeof(aiVector3D);
    }
    
    CHECK_OPENGL_ERROR();
    
    return norms;
  }
  
  ArrayBuffers copyUVs(size_t numGroups, const aiScene *scene, size_t &size) {
    using ArrayType = array_to_class_t<TexType>;
    assert(numGroups);
    
    ArrayBuffers UVs(numGroups, NO_GEN);
    std::vector<ArrayType> UVsCopy;
    
    for (size_t g = 0; g != numGroups; g++) {
      const aiMesh &mesh = *scene->mMeshes[g];
      
      if (mesh.HasTextureCoords(0)) {
        UVs.gen(g);
        UVs.bind(g);
        UVsCopy.resize(mesh.mNumVertices);
        for (size_t v = 0; v != UVsCopy.size(); v++) {
          UVsCopy[v][0] = mesh.mTextureCoords[0][v].x;
          UVsCopy[v][1] = mesh.mTextureCoords[0][v].y;
        }
        glBufferData(
          GL_ARRAY_BUFFER,
          UVsCopy.size() * sizeof(ArrayType),
          UVsCopy.data(),
          GL_STATIC_DRAW
        );
        
        size += UVsCopy.size() * sizeof(ArrayType);
      }
    }
    
    CHECK_OPENGL_ERROR();
    
    return UVs;
  }
  
  struct IDWeight {
    BoneIDsType ids;
    BoneWeightsType weights;
  };
  
  void copyIDWeight(
    std::vector<IDWeight> &idWeightsCopy,
    BoneIDType idAccum,
    const aiMesh &mesh
  ) {
    idWeightsCopy.resize(mesh.mNumVertices);
    std::memset(idWeightsCopy.data(), 0, idWeightsCopy.size() * sizeof(IDWeight));
    
    for (size_t b = 0; b != mesh.mNumBones; b++) {
      const aiBone &bone = *mesh.mBones[b];
      
      for (size_t w = 0; w != bone.mNumWeights; w++) {
        const aiVertexWeight weight = bone.mWeights[w];
        IDWeight &idWeight = idWeightsCopy[weight.mVertexId];
        
        size_t s = 0;
        while (idWeight.weights[s] != 0.0f) {
          s++;
          assert(s < MAX_BONES_PER_VERTEX);
        }
        idWeight.ids[s] = idAccum + static_cast<BoneIDType>(b);
        idWeight.weights[s] = weight.mWeight;
      }
    }
  }
  
  ArrayBuffers copyIDWeights(
    size_t numGroups,
    const aiScene *scene,
    size_t &size
  ) {
    assert(numGroups);
    
    if (!scene->HasAnimations()) {
      return {};
    }
    
    ArrayBuffers idWeights(numGroups);
    std::vector<IDWeight> idWeightsCopy;
    BoneIDType idAccum = 0;
    
    for (size_t g = 0; g != numGroups; g++) {
      const aiMesh &mesh = *scene->mMeshes[g];
      copyIDWeight(idWeightsCopy, idAccum, mesh);
      idAccum += mesh.mNumBones;
      
      idWeights.bind(g);
      glBufferData(
        GL_ARRAY_BUFFER,
        idWeightsCopy.size() * sizeof(IDWeight),
        idWeightsCopy.data(),
        GL_STATIC_DRAW
      );
      
      size += idWeightsCopy.size() * sizeof(IDWeight);
    }
    
    CHECK_OPENGL_ERROR();
    
    return idWeights;
  }
  
  ElementBuffers copyElems(
    size_t numGroups,
    std::vector<ElemType> &indiciesNum,
    const aiScene *scene,
    size_t &size
  ) {
    assert(numGroups);
    
    ElementBuffers elems(numGroups);
    std::vector<ElemType> elemsCopy;
    
    for (size_t g = 0; g != numGroups; g++) {
      const aiMesh &mesh = *scene->mMeshes[g];
      
      elemsCopy.resize(mesh.mNumFaces * 3);
      for (size_t f = 0; f != mesh.mNumFaces; f++) {
        assert(mesh.mFaces[f].mNumIndices == 3);
        elemsCopy[f * 3 + 0] = mesh.mFaces[f].mIndices[0];
        elemsCopy[f * 3 + 1] = mesh.mFaces[f].mIndices[1];
        elemsCopy[f * 3 + 2] = mesh.mFaces[f].mIndices[2];
      }
      elems.bind(g);
      glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,
        elemsCopy.size() * ELEM_SIZE,
        elemsCopy.data(),
        GL_STATIC_DRAW
      );
      indiciesNum[g] = static_cast<ElemType>(elemsCopy.size());
      size += elemsCopy.size() * ELEM_SIZE;
    }
    
    CHECK_OPENGL_ERROR();
    
    return elems;
  }
  
  struct MeshBuffers {
    ArrayBuffers verts;
    ArrayBuffers norms;
    ArrayBuffers uvs;
    ArrayBuffers idWeights;
    ElementBuffers elems;
  };
  
  VertexArrays makeVAOs(
    size_t numGroups,
    MeshBuffers &buffers
  ) {
    assert(numGroups);
    
    VertexArrays vaos(numGroups);
    const bool HAS_BONE_ID_WEIGHTS = buffers.idWeights.size();
    
    for (size_t g = 0; g != numGroups; g++) {
      vaos.bind(g);
      
      buffers.verts.bind(g);
      enablePos();
      posPointer(0, 0);
      
      buffers.norms.bind(g);
      enableNormal();
      normalPointer(0, 0);
      
      if (buffers.uvs.exists(g)) {
        buffers.uvs.bind(g);
        enableTexturePos();
        texturePosPointer(0, 0);
      }
      
      if (HAS_BONE_ID_WEIGHTS) {
        buffers.idWeights.bind(g);
        enableBoneID();
        enableBoneWeight();
        boneIDPointer(BONE_IDS_SIZE + BONE_WGHTS_SIZE, 0);
        boneWeightPointer(BONE_IDS_SIZE + BONE_WGHTS_SIZE, BONE_IDS_SIZE);
      }
      
      buffers.elems.bind(g);
    }
    
    CHECK_OPENGL_ERROR();
    
    return vaos;
  }
  
  std::vector<MeshImpl::MaterialID> copyMatIndicies(
    size_t numGroups,
    const aiScene *scene
  ) {
    assert(numGroups);
    
    std::vector<MeshImpl::MaterialID> matIndicies;
    matIndicies.reserve(numGroups);
    
    for (size_t g = 0; g != scene->mNumMeshes; g++) {
      matIndicies.push_back(scene->mMeshes[g]->mMaterialIndex);
    }
    
    return matIndicies;
  }
  
  template <typename T, typename U, std::enable_if_t<(sizeof(U) > sizeof(U *)), int> = 0>
  T cast(const U &);

  template <typename T, typename U, std::enable_if_t<sizeof(U) <= sizeof(U *), int> = 0>
  T cast(const U);
  
  template <>
  glm::vec4 cast(const aiColor4D &aiColor) {
    return {aiColor.r, aiColor.g, aiColor.b, aiColor.a};
  }
  
  template <>
  Graphics3D::FragType cast(const aiShadingMode shader) {
    using namespace Graphics3D;
    
    switch (shader) {
      case aiShadingMode_Flat:
      case aiShadingMode_Gouraud:
      case aiShadingMode_Phong:
        return FragType::PHONG;
      case aiShadingMode_Blinn:
        return FragType::BLINN;
      case aiShadingMode_Toon:
        return FragType::TOON;
      case aiShadingMode_OrenNayar:
        return FragType::OREN_NAYER;
      case aiShadingMode_Minnaert:
        return FragType::MINNAERT;
      case aiShadingMode_CookTorrance:
        return FragType::COOK_TORRANCE;
      case aiShadingMode_NoShading:
        return FragType::SOLID;
      case aiShadingMode_Fresnel:
        return FragType::FRESNEL;
      
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
  
  static const aiTextureMapMode DEFAULT_TEX_MAP_MODE = aiTextureMapMode_Wrap;
  
  Res::ID getTexture(
    aiTextureType type,
    const aiMaterial *material,
    const std::string &folder
  ) {
    aiString aiPath;
    material->Get(AI_MATKEY_TEXTURE(type, 0), aiPath);
    
    if (aiPath.length) {
      Graphics3D::TexParams params;
      
      aiTextureMapMode mapping = DEFAULT_TEX_MAP_MODE;
      material->Get(AI_MATKEY_MAPPINGMODE_U(type, 0), mapping);
      params.wrapS = cast<Graphics3D::TexWrap>(mapping);
      
      mapping = DEFAULT_TEX_MAP_MODE;
      material->Get(AI_MATKEY_MAPPINGMODE_V(type, 0), mapping);
      params.wrapT = cast<Graphics3D::TexWrap>(mapping);
      
      aiTextureFlags flags = static_cast<aiTextureFlags>(0);
      material->Get(AI_MATKEY_TEXFLAGS(type, 0), flags);
      
      params.invert = flags & aiTextureFlags_Invert;
      params.hasAlpha = !(flags & aiTextureFlags_IgnoreAlpha);
      
      return {folder + aiPath.C_Str(), params};
    } else {
      return {};
    }
  }
  
  Graphics3D::Material copyMat(
    const aiMaterial *otherMaterial,
    const std::string &folder
  ) {
    Graphics3D::Material material;
    
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
    
    material.diffuseTexture = getTexture(aiTextureType_DIFFUSE, otherMaterial, folder);
    material.ambientTexture = getTexture(aiTextureType_AMBIENT, otherMaterial, folder);
    material.specularTexture = getTexture(aiTextureType_SPECULAR, otherMaterial, folder);
    
    return material;
  }
  
  std::vector<Graphics3D::Material> copyMats(
    const aiScene *scene,
    const std::string &folder
  ) {
    const size_t numMaterials = scene->mNumMaterials;
    std::vector<Graphics3D::Material> materials;
    materials.reserve(numMaterials);
    
    for (size_t m = 0; m != numMaterials; m++) {
      materials.emplace_back(copyMat(scene->mMaterials[m], folder));
    }
    
    return materials;
  }
  
  static const aiShadingMode DEFAULT_SHADING_MODE = aiShadingMode_Phong;
  
  std::vector<Graphics3D::ProgType> copyProgTypes(
    const aiScene *scene,
    const std::vector<MeshImpl::MaterialID> &matIndicies
  ) {
    const size_t NUM_GROUPS = matIndicies.size();
    const bool IS_ANIMATED = scene->HasAnimations();
    std::vector<Graphics3D::ProgType> progTypes;
    progTypes.reserve(NUM_GROUPS);
    
    for (size_t g = 0; g != NUM_GROUPS; g++) {
      aiShadingMode shadingMode = DEFAULT_SHADING_MODE;
      scene->mMaterials[matIndicies[g]]->Get(AI_MATKEY_SHADING_MODEL, shadingMode);
      progTypes.push_back({IS_ANIMATED, cast<Graphics3D::FragType>(shadingMode)});
    }
    
    return progTypes;
  }
}

void Platform::setImporterProps(Assimp::Importer &importer) {
  importer.SetPropertyInteger(AI_CONFIG_PP_LBW_MAX_WEIGHTS, MAX_BONES_PER_VERTEX);
}

Mesh::Ptr Platform::loadMesh(const aiScene *scene, const std::string &folder) {
  assert(scene->HasMeshes());
  assert(scene->HasMaterials());
  
  size_t size = 0;
  const size_t numGroups = scene->mNumMeshes;
  std::vector<ElemType> indiciesNum(numGroups);
  MeshBuffers buffers {
    copyVerts(numGroups, scene, size),
    copyNorms(numGroups, scene, size),
    copyUVs(numGroups, scene, size),
    copyIDWeights(numGroups, scene, size),
    copyElems(numGroups, indiciesNum, scene, size)
  };
  VertexArrays vaos = makeVAOs(numGroups, buffers);
  std::vector<MeshImpl::MaterialID> matIndicies = copyMatIndicies(numGroups, scene);
  std::vector<Graphics3D::Material> materials = copyMats(scene, folder);
  std::vector<Graphics3D::ProgType> progTypes = copyProgTypes(scene, matIndicies);
  
  MeshImpl::Ptr mesh = std::make_shared<MeshImpl>();
  mesh->matIndicies.swap(matIndicies);
  mesh->materials.swap(materials);
  mesh->progTypes.swap(progTypes);
  mesh->indiciesNum.swap(indiciesNum);
  mesh->verts.swap(buffers.verts);
  mesh->norms.swap(buffers.norms);
  mesh->uvs.swap(buffers.uvs);
  mesh->idWeights.swap(buffers.idWeights);
  mesh->elems.swap(buffers.elems);
  mesh->byteSize = size;
  
  return mesh;
}

#endif
