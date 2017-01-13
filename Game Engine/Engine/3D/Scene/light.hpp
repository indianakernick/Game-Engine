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
#include "../color.hpp"

namespace Scene {
  class Light : public Node {
  public:
    enum Type {
      DIRECT,
      SPHERE,
      CIRC_SPOT,
      RECT_SPOT
    };
    
    struct Properties {
      Type type;
      Color3F color;
      float intensity;
    };
    
    struct Angles {
      float hori;
      float vert;
    };
  
    Light(Game::Actor::ID, const glm::mat4 &, const Properties &);
    Light(Game::Actor::ID, const glm::mat4 &, const Properties &, float);
    Light(Game::Actor::ID, const glm::mat4 &, const Properties &, Angles);
    ~Light() = default;
    
    Type getType() const;
    const Color3F &getColor() const;
    float getIntensity() const;
    ///Get the angle that defineds the cone of a circular spot light
    float getAngle() const;
    ///Get the horizontal and vertical angles that define the pyrimid of
    ///a rectangular spot light
    Angles getAngle2() const;
    
    void setColor(const Color3F &);
    void setIntensity(float);
    void setAngle(float);
    void setAngle2(Angles);
    
  private:
    Properties props;
    
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
