//
//  light.hpp
//  Game Engine
//
//  Created by Indi Kernick on 13/1/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_3d_scene_light_hpp
#define engine_3d_scene_light_hpp

#include "node.hpp"

namespace Scene {
  class Light final : public Node {
  public:
    using Ptr = std::shared_ptr<Light>;
  
    enum Type {
      DIRECT,
      SPHERE,
      SPOT
    };
    
    ///Properties that all light types share
    struct CommonProps {
      Type type;
      glm::vec3 color;
      float intensity;
    };
    
    ///Properties of all light types
    struct AllProps {
      Type type;
      glm::vec3 color;
      float intensity;
      float angle;
    };
  
    Light(Game::Actor::ID, const glm::mat4 &, const CommonProps &);
    Light(Game::Actor::ID, const glm::mat4 &, const CommonProps &, float);
    ~Light() = default;
    
    AllProps getAllProps() const;
    
    Type getType() const;
    const glm::vec3 &getColor() const;
    float getIntensity() const;
    ///Get the angle that defineds the cone of a spot light
    float getAngle() const;
    
    void setColor(const glm::vec3 &);
    void setIntensity(float);
    void setAngle(float);
    
  private:
    CommonProps props;
    float angle;
  };
}

#endif
