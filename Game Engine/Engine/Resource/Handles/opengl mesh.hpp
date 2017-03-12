//
//  opengl mesh.hpp
//  Game Engine
//
//  Created by Indi Kernick on 2/1/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_resource_handles_opengl_mesh_hpp
#define engine_resource_handles_opengl_mesh_hpp

#ifdef USE_OPENGL

#include "../../Application/opengl.hpp"
#include "../handle.hpp"
#include <vector>
#include <cassert>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/quaternion.hpp>
#include "../../3D/material.hpp"
#include <unordered_map>
#include <string>
#include <memory>
#include "../../3D/program type.hpp"

namespace Res {
  class MeshOpenGL : public Handle {
  friend class MeshLoaderOpenGL;
  public:
    using Ptr = std::shared_ptr<MeshOpenGL>;
  
    using Time = double;
  
    //corresponds to aiVectorKey and aiQuatKey
    template <typename T>
    struct SubChannelKey {
      Time time;
      T value;
    };
    
    template <typename T>
    using SubChannel = std::vector<SubChannelKey<T>>;
    
    using BoneID = uint16_t;
    using ChannelID = uint16_t;
    using AnimationID = uint16_t;
    //corresponds to aiMesh
    using GroupID = uint8_t;
    using MaterialID = uint8_t;
    using AnimNames = std::unordered_map<std::string, AnimationID>;
    using ChannelNames = std::unordered_map<std::string, ChannelID>;
    
    //corresponds to aiNodeAnim
    struct Channel {
      /*
      Some animations only utilize some of the available channels so
      dummy channels have to fill in the gaps.
      
      This approach will use a bit more memory (because most animations will 
      utilize all bones) than a std::unordered_map, but it will be faster.
      
      If a Bone finds that its cooresponding channel is a dummy then it
      will use its own transformation instead of the one in the channel
      */
      bool dummy = true;
      SubChannel<glm::vec3> translation;
      SubChannel<glm::quat> rotation;
      SubChannel<glm::vec3> scaling;
    };
    
    using Channels = std::vector<Channel>;
    
    //corresponds to aiAnimation
    struct Animation {
      Time duration;
      double ticksPerSecond;
      Channels channels;
    };
    
    //corresponds to aiBone
    struct Bone {
      ChannelID channel;
      GroupID group;
      glm::mat4 offset;
    };
    
    /*
    There may be many Bones for each BoneNode.
    A single bone may be spread across more than one mesh because it may
    use different materials for different parts of it.
    The Bone's ChannelID maps to the BoneNode and the Channel
    */
    
    //corresponds to aiNode
    struct BoneNode {
      /*
      If an Animation doesn't have a Channel for a Bone then this will
      be used instead
      */
      glm::mat4 transform;
      std::vector<ChannelID> children;
    };
    
    using Bones = std::vector<Bone>;
    using Anims = std::vector<Animation>;
    using BoneNodes = std::vector<BoneNode>;
    
    MeshOpenGL(GroupID numGroups,
               MaterialID numMaterials,
               const std::vector<MaterialID> &matIndicies);
    ~MeshOpenGL();
  
    const std::vector<GLuint> &getVAOs() const;
    const std::vector<MaterialID> &getMatIndicies() const;
    const std::vector<Graphics3D::Material> &getMaterials() const;
    const std::vector<unsigned> &getIndiciesNum() const;
    const std::vector<Graphics3D::ProgType> &getProgTypes() const;
    const Anims &getAnimations() const;
    const AnimNames &getAnimNames() const;
    const ChannelNames &getChannelNames() const;
    const Bones &getBones() const;
    const BoneNodes &getBoneNodes() const;
    
    bool hasAnimations() const;
  private:
    std::vector<GLuint> VAOs;
    std::vector<MaterialID> matIndicies;
    std::vector<Graphics3D::Material> materials;
    std::vector<unsigned> indiciesNum;
    std::vector<Graphics3D::ProgType> progTypes;
    std::vector<GLuint> buffers;
    
    Anims animations;
    AnimNames animNames;
    ChannelNames channelNames;
    Bones bones;
    BoneNodes boneNodes;
  };
}

#endif

#endif
