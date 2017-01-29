//
//  assimp serial.cpp
//  Game Engine
//
//  Created by Indi Kernick on 27/1/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "assimp serial.hpp"

const char *printBehav(aiAnimBehaviour behav) {
  switch (behav) {
    case aiAnimBehaviour_DEFAULT:
      return "Default";
    case aiAnimBehaviour_CONSTANT:
      return "Constant";
    case aiAnimBehaviour_LINEAR:
      return "Linear";
    case aiAnimBehaviour_REPEAT:
      return "Repeat";
    default:
      return "INVALID VALUE";
  }
}

void printAnims(aiAnimation ** const anims, unsigned int numAnims) {
  for (unsigned int a = 0; a < numAnims; a++) {
    const aiAnimation *anim = anims[a];
    std::cout << "Anim " << a << " \"" << anim->mName.C_Str() << "\"\n";
    std::cout << "  Duration         " << anim->mDuration << '\n';
    std::cout << "  Ticks per second " << anim->mTicksPerSecond << '\n';
    std::cout << "  Channels         " << anim->mNumChannels << '\n';
    std::cout << "  Mesh channels    " << anim->mNumMeshChannels << '\n';
    std::cout << '\n';
    for (unsigned int c = 0; c < anim->mNumChannels; c++) {
      const aiNodeAnim *channel = anim->mChannels[c];
      std::cout << "  Channel " << c << " \"" << channel->mNodeName.C_Str() << "\"\n";
      std::cout << "    Position keys " << channel->mNumPositionKeys << '\n';
      std::cout << "    Rotation keys " << channel->mNumRotationKeys << '\n';
      std::cout << "    Scaling keys  " << channel->mNumScalingKeys << '\n';
      std::cout << "    Pre state     " << printBehav(channel->mPreState) << '\n';
      std::cout << "    Post state    " << printBehav(channel->mPostState) << '\n';
    }
    for (unsigned int c = 0; c < anim->mNumMeshChannels; c++) {
      const aiMeshAnim *channel = anim->mMeshChannels[c];
      std::cout << "  Mesh channel " << c << " \"" << channel->mName.C_Str() << "\"\n";
      std::cout << "    Keys " << channel->mNumKeys << '\n';
    }
  }
}

const char *printVector(const aiVector2D &vec) {
  std::cout << vec.x << ", " << vec.y;
  return "";
}

const char *printVector(const aiVector3D &vec) {
  std::cout << vec.x << ", " << vec.y << ", " << vec.z;
  return "";
}

const char *printColor(const aiColor3D &color) {
  std::cout << color.r << ", " << color.g << ", " << color.b;
  return "";
}

const char *printColor(const aiColor4D &color) {
  std::cout << color.r << ", " << color.g << ", " << color.b << ", " << color.a;
  return "";
}

void printCameras(aiCamera ** const cameras, unsigned int numCameras) {
  for (unsigned int c = 0; c < numCameras; c++) {
    const aiCamera *camera = cameras[c];
    std::cout << "Camera " << c << " \"" << camera->mName.C_Str() << "\"\n";
    std::cout << "  Position " << printVector(camera->mPosition) << '\n';
    std::cout << "  Up       " << printVector(camera->mUp) << '\n';
    std::cout << "  Look at  " << printVector(camera->mLookAt) << '\n';
    std::cout << "  Aspect   " << camera->mAspect << '\n';
    std::cout << "  Near     " << camera->mClipPlaneNear << '\n';
    std::cout << "  Far      " << camera->mClipPlaneFar << '\n';
    std::cout << "  FOV x    " << camera->mHorizontalFOV << '\n';
  }
  std::cout << '\n';
}

const char *printLightType(aiLightSourceType type) {
  switch (type) {
    case aiLightSource_UNDEFINED:
      return "Undefined";
    case aiLightSource_DIRECTIONAL:
      return "Directional";
    case aiLightSource_POINT:
      return "Point";
    case aiLightSource_SPOT:
      return "Spot";
    default:
      return "INVALID VALUE";
  }
}

void printLights(aiLight ** const lights, unsigned int numLights) {
  for (unsigned int l = 0; l < numLights; l++) {
    const aiLight *light = lights[l];
    std::cout << "Light " << l << " \"" << light->mName.C_Str() << "\"\n";
    std::cout << "  Type            " << printLightType(light->mType) << '\n';
    std::cout << "  Position        " << printVector(light->mPosition) << '\n';
    std::cout << "  Direction       " << printVector(light->mDirection) << '\n';
    std::cout << "  Ambient color   " << printColor(light->mColorAmbient) << '\n';
    std::cout << "  Diffuse color   " << printColor(light->mColorDiffuse) << '\n';
    std::cout << "  Specular color  " << printColor(light->mColorSpecular) << '\n';
    std::cout << "  Inner angle     " << light->mAngleInnerCone << '\n';
    std::cout << "  Outer angle     " << light->mAngleOuterCone << '\n';
    std::cout << "  Atten Constant  " << light->mAttenuationConstant << '\n';
    std::cout << "  Atten Linear    " << light->mAttenuationLinear << '\n';
    std::cout << "  Atten Quadratic " << light->mAttenuationQuadratic << '\n';
  }
  std::cout << '\n';
}

const char *printSemantic(unsigned int sem) {
  switch (sem) {
    case aiTextureType_NONE:
      return "None";
    case aiTextureType_DIFFUSE:
      return "Diffuse";
    case aiTextureType_SPECULAR:
      return "Specular";
    case aiTextureType_AMBIENT:
      return "Ambient";
    case aiTextureType_EMISSIVE:
      return "Emissive";
    case aiTextureType_HEIGHT:
      return "Height";
    case aiTextureType_NORMALS:
      return "Normals";
    case aiTextureType_SHININESS:
      return "Shininess";
    case aiTextureType_OPACITY:
      return "Opacity";
    case aiTextureType_DISPLACEMENT:
      return "Displacement";
    case aiTextureType_LIGHTMAP:
      return "Lightmap";
    case aiTextureType_REFLECTION:
      return "Reflection";
    case aiTextureType_UNKNOWN:
      return "Unknown";
    default:
      return "INVALID VALUE";
  }
}

const char *printMatPropType(aiPropertyTypeInfo type) {
  switch (type) {
    case aiPTI_Float:
      return "Float";
    case aiPTI_String:
      return "String";
    case aiPTI_Integer:
      return "Integer";
    case aiPTI_Buffer:
      return "Buffer";
    default:
      return "INVALID VALUE";
  }
}

const char *printMatPropData(aiPropertyTypeInfo type,
                             const char *data,
                             unsigned int size) {
  switch (type) {
    case aiPTI_Float: {
      assert(size % 4 == 0);
      const float *floatData = reinterpret_cast<const float *>(data);
      unsigned int floatSize = size / 4;
      for (unsigned int f = 0; f < floatSize; f++) {
        std::cout << floatData;
        if (f != floatSize - 1) {
          std::cout << ", ";
        }
      }
      break;
    }
    
    case aiPTI_String:
      std::cout.write(data, size);
      break;
    
    case aiPTI_Integer: {
      assert(size % 4 == 0);
      const int *intData = reinterpret_cast<const int *>(data);
      unsigned int intSize = size / 4;
      for (unsigned int i = 0; i < intSize; i++) {
        std::cout << intData;
        if (i != intSize - 1) {
          std::cout << ", ";
        }
      }
      break;
    }
    
    case aiPTI_Buffer:
      std::cout.write(data, size);
      break;
    
    default:
      std::cout << "INVALID VALUE";
  }
  return "";
}

void printProperty(const aiMaterialProperty *prop) {
  std::cout << "  \"" << prop->mKey.C_Str() << "\"\n";
  std::cout << "    Index    " << prop->mIndex << '\n';
  std::cout << "    Semantic " << printSemantic(prop->mSemantic) << '\n';
  std::cout << "    Type     " << printMatPropType(prop->mType) << '\n';
  std::cout << "    Data     " << printMatPropData(prop->mType,
                                                   prop->mData,
                                                   prop->mDataLength) << '\n';
}

void printMaterials(aiMaterial ** const materials, unsigned int numMaterials) {
  for (unsigned int m = 0; m < numMaterials; m++) {
    const aiMaterial *mat = materials[m];
    std::cout << "Material " << m << " \"";
    aiString str;
    mat->Get(AI_MATKEY_NAME, str);
    std::cout << str.C_Str() << "\"\n";
    std::cout << "  Properties " << mat->mNumProperties << '\n';
    for (unsigned int p = 0; p < mat->mNumProperties; p++) {
      printProperty(mat->mProperties[p]);
    }
  }
  std::cout << '\n';
}

void printMeshes(aiMesh **meshes, unsigned int numMeshes) {
  for (unsigned int m = 0; m < numMeshes; m++) {
    const aiMesh *mesh = meshes[m];
    std::cout << "Mesh " << m << " \"" << mesh->mName.C_Str() << "\"\n";
    std::cout << "  Vertices    " << mesh->mNumVertices << '\n';
    std::cout << "  Faces       " << mesh->mNumFaces << '\n';
    std::cout << "  Anim meshes " << mesh->mNumAnimMeshes << '\n';
    std::cout << "  Bones       " << mesh->mNumBones << '\n';
    for (unsigned int b = 0; b < mesh->mNumBones; b++) {
      const aiBone *bone = mesh->mBones[b];
      std::cout << "  Bone " << b << " \"" << bone->mName.C_Str() << "\"\n";
      std::cout << "    Weights " << bone->mNumWeights << '\n';
    }
  }
  std::cout << '\n';
}

void printTextures(aiTexture **textures, unsigned int numTextures) {
  for (unsigned int t = 0; t < numTextures; t++) {
    const aiTexture *tex = textures[t];
    std::cout << "Texture " << t << '\n';
    std::cout << "  Width  " << tex->mWidth << '\n';
    std::cout << "  Height " << tex->mHeight << '\n';
    std::cout << "  Format " << tex->achFormatHint << '\n';
  }
  std::cout << '\n';
}

void printNodes(aiNode *node, unsigned int depth = 0) {
  std::string depthStr(depth * 4, ' ');
  std::cout << depthStr << "Node \"" << node->mName.C_Str() << "\"\n";
  std::cout << depthStr << "  Meshes   " << node->mNumMeshes << '\n';
  for (unsigned int m = 0; m < node->mNumMeshes; m++) {
    std::cout << depthStr << "  Mesh     " << m << '\n';
  }
  std::cout << depthStr << "  Children " << node->mNumChildren << '\n';
  for (unsigned int n = 0; n < node->mNumChildren; n++) {
    printNodes(node->mChildren[n], depth + 1);
  }
}

void printScene(const aiScene *scene) {
  std::cout << "Animations " << scene->mNumAnimations << '\n';
  std::cout << "Cameras    " << scene->mNumCameras << '\n';
  std::cout << "Lights     " << scene->mNumLights << '\n';
  std::cout << "Materials  " << scene->mNumMaterials << '\n';
  std::cout << "Meshes     " << scene->mNumMeshes << '\n';
  std::cout << "Textures   " << scene->mNumTextures << '\n';
  std::cout << '\n';
  
  printAnims(scene->mAnimations, scene->mNumAnimations);
  printCameras(scene->mCameras, scene->mNumCameras);
  printLights(scene->mLights, scene->mNumLights);
  printMaterials(scene->mMaterials, scene->mNumMaterials);
  printMeshes(scene->mMeshes, scene->mNumMeshes);
  printTextures(scene->mTextures, scene->mNumTextures);
  printNodes(scene->mRootNode);
}
