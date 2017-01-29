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
  class Light : public Node {
  public:
    using Ptr = std::shared_ptr<Light>;
  
    enum Type {
      DIRECT,
      SPHERE,
      CIRC_SPOT,
      RECT_SPOT
    };
    
    ///Properties that all light types share
    struct CommonProps {
      Type type;
      glm::vec3 color;
      float intensity;
    };
    
    ///The angles of a rectangular spot light
    struct Angles {
      float hori;
      float vert;
    };
    
    ///Properties of all light types
    struct AllProps {
      Type type;
      glm::vec3 color;
      float intensity;
      union {
        float angle;
        float horiAngle;
      };
      float vertAngle;
    };
  
    Light(Game::Actor::ID, const glm::mat4 &, const CommonProps &);
    Light(Game::Actor::ID, const glm::mat4 &, const CommonProps &, float);
    Light(Game::Actor::ID, const glm::mat4 &, const CommonProps &, Angles);
    ~Light() = default;
    
    AllProps getAllProps() const;
    
    Type getType() const;
    const glm::vec3 &getColor() const;
    float getIntensity() const;
    ///Get the angle that defineds the cone of a circular spot light
    float getAngle() const;
    ///Get the horizontal and vertical angles that define the pyrimid of
    ///a rectangular spot light
    Angles getAngle2() const;
    
    void setColor(const glm::vec3 &);
    void setIntensity(float);
    void setAngle(float);
    void setAngle2(Angles);
    
  private:
    CommonProps props;
    
    union {
      //circ spot
      float angle;
      //rect spot
      float horiAngle;
    };
    //rect spot
    float vertAngle;
  };
}

#endif
