//
//  mesh.hpp
//  Game Engine
//
//  Created by Indi Kernick on 14/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_resource_handles_mesh_hpp
#define engine_resource_handles_mesh_hpp

#include "../handle.hpp"
#include "../../Platform/Interface/mesh.hpp"
#include <vector>
#include <string>
#include <unordered_map>
#include <glm/vec3.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/mat4x4.hpp>

namespace Res {
  class Mesh final : public Handle {
  friend class MeshLoader;
  public:
    using Ptr = std::shared_ptr<Mesh>;
  
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
    using AnimID = uint16_t;
    using AnimNames = std::unordered_map<std::string, AnimID>;
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
    struct Anim {
      Time duration;
      double ticksPerSecond;
      Channels channels;
    };
    
    //corresponds to aiBone
    struct Bone {
      ChannelID channel;
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
    using Anims = std::vector<Anim>;
    using BoneNodes = std::vector<BoneNode>;
  
    Mesh(Platform::Mesh::Ptr);
    ~Mesh() = default;
    
    Platform::Mesh::Ptr getMesh() const;
    const Anims &getAnims() const;
    const AnimNames &getAnimNames() const;
    const ChannelNames &getChannelNames() const;
    const Bones &getBones() const;
    const BoneNodes &getBoneNodes() const;
    
  private:
    Platform::Mesh::Ptr mesh;
    Anims anims;
    AnimNames animNames;
    ChannelNames channelNames;
    Bones bones;
    BoneNodes boneNodes;
  };
}

#endif
