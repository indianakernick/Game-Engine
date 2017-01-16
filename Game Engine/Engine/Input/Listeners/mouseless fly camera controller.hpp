//
//  mouseless fly camera controller.hpp
//  Game Engine
//
//  Created by Indi Kernick on 15/1/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_input_listeners_mouseless_fly_camera_controller_hpp
#define engine_input_listeners_mouseless_fly_camera_controller_hpp

#include "../event listener.hpp"
#include <glm/mat4x4.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <bitset>

struct Bindings {
  Input::Key::Type moveForward = Input::Key::W;
  Input::Key::Type moveRight = Input::Key::D;
  Input::Key::Type moveBackward = Input::Key::S;
  Input::Key::Type moveLeft = Input::Key::A;
  
  Input::Key::Type moveUp = Input::Key::SPACE;
  Input::Key::Type moveDown = Input::Key::SHIFT;
  
  Input::Key::Type lookUp = Input::Key::UP;
  Input::Key::Type lookRight = Input::Key::RIGHT;
  Input::Key::Type lookDown = Input::Key::DOWN;
  Input::Key::Type lookLeft = Input::Key::LEFT;
};

struct Speed {
  ///Units per second
  float move = 2.0;
  ///Units per second
  float vert = 2.0;
  ///Radians per second
  float look = 0.75;
};

class CamControlFlyMouseless : public Input::EventListener {
public:
  using Ptr = std::shared_ptr<CamControlFlyMouseless>;
  
  explicit CamControlFlyMouseless(const Bindings & = {}, const Speed & = {});
  
  void update(uint64_t);
  
  const glm::mat4 &getToWorld() const;
private:
  glm::mat4 toWorld;
  float yaw = 0.0f;
  float pitch = 0.0f;
  glm::vec3 pos;
  
  Bindings bindings;
  Speed speed;
  std::bitset<10> keys;
  
  enum {
    MOVE_FORWARD,
    MOVE_RIGHT,
    MOVE_BACKWARD,
    MOVE_LEFT,
    MOVE_UP,
    MOVE_DOWN,
    LOOK_UP,
    LOOK_RIGHT,
    LOOK_DOWN,
    LOOK_LEFT
  };
  
  bool setKey(Input::Key::Type, bool);
  
  bool onKeyDown(const Input::KeyDown *) override;
  bool onKeyUp(const Input::KeyUp *) override;
};

#endif
