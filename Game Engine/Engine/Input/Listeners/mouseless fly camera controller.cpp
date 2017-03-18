//
//  mouseless fly camera controller.cpp
//  Game Engine
//
//  Created by Indi Kernick on 15/1/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "mouseless fly camera controller.hpp"

CamControlFlyMouseless::CamControlFlyMouseless(const glm::vec3 &pos,
                                               float yaw,
                                               float pitch)
  : yaw(yaw),
    pitch(pitch),
    pos(pos),
    bindings({}),
    speed({}) {
  using namespace std::placeholders;
  
  evtMan->addListener(
    Input::KeyDown::TYPE,
    std::bind(
      std::mem_fn(
        &CamControlFlyMouseless::onKeyDown
      ),
      this,
      _1
    )
  );
  evtMan->addListener(
    Input::KeyUp::TYPE,
    std::bind(
      std::mem_fn(
        &CamControlFlyMouseless::onKeyUp
      ),
      this,
      _1
    )
  );
}

CamControlFlyMouseless::CamControlFlyMouseless(const Bindings &bindings,
                                               const Speed &speed,
                                               const glm::vec3 &pos,
                                               float yaw,
                                               float pitch)
  : yaw(yaw),
    pitch(pitch),
    pos(pos),
    bindings(bindings),
    speed(speed) {
  using namespace std::placeholders;
  
  evtMan->addListener(
    Input::KeyDown::TYPE,
    std::bind(
      std::mem_fn(
        &CamControlFlyMouseless::onKeyDown
      ),
      this,
      _1
    )
  );
  evtMan->addListener(
    Input::KeyUp::TYPE,
    std::bind(
      std::mem_fn(
        &CamControlFlyMouseless::onKeyUp
      ),
      this,
      _1
    )
  );
}

CamControlFlyMouseless::~CamControlFlyMouseless() {
  using namespace std::placeholders;
  
  evtMan->remListener(
    Input::KeyDown::TYPE,
    std::bind(
      std::mem_fn(
        &CamControlFlyMouseless::onKeyDown
      ),
      this,
      _1
    )
  );
  evtMan->remListener(
    Input::KeyUp::TYPE,
    std::bind(
      std::mem_fn(
        &CamControlFlyMouseless::onKeyUp
      ),
      this,
      _1
    )
  );
}

void CamControlFlyMouseless::update(uint64_t delta) {
  const float deltaSec = delta / 1000.0f;
  const float move = speed.move * deltaSec;
  const float vert = speed.vert * deltaSec;
  const float look = speed.look * deltaSec;
  
  if (keys[MOVE_UP]) {
    pos.y += vert;
  }
  if (keys[MOVE_DOWN]) {
    pos.y -= vert;
  }
  if (keys[LOOK_UP]) {
    pitch += look;
  }
  if (keys[LOOK_RIGHT]) {
    yaw -= look;
  }
  if (keys[LOOK_DOWN]) {
    pitch -= look;
  }
  if (keys[LOOK_LEFT]) {
    yaw += look;
  }
  
  glm::mat3 yawMat = glm::eulerAngleY(yaw);
  
  if (keys[MOVE_FORWARD]) {
    pos += yawMat * glm::vec3(0.0f, 0.0f, -move);
  }
  if (keys[MOVE_RIGHT]) {
    pos += yawMat * glm::vec3(move, 0.0f, 0.0f);
  }
  if (keys[MOVE_BACKWARD]) {
    pos += yawMat * glm::vec3(0.0f, 0.0f, move);
  }
  if (keys[MOVE_LEFT]) {
    pos += yawMat * glm::vec3(-move, 0.0f, 0.0f);
  }
  
  toWorld = glm::translate({}, pos) * glm::eulerAngleYX(yaw, pitch);
}

void CamControlFlyMouseless::setPos(const glm::vec3 &newPos) {
  pos = newPos;
}

void CamControlFlyMouseless::setLook(float newYaw, float newPitch) {
  yaw = newYaw;
  pitch = newPitch;
}

const glm::mat4 &CamControlFlyMouseless::getToWorld() const {
  return toWorld;
}

void CamControlFlyMouseless::setKey(Input::Key::Type key, bool status) {
  //it really bothers me that i can't use a switch here.
  //I love switches!
         if (key == bindings.moveForward) {
    keys[MOVE_FORWARD] = status;
  } else if (key == bindings.moveRight) {
    keys[MOVE_RIGHT] = status;
  } else if (key == bindings.moveBackward) {
    keys[MOVE_BACKWARD] = status;
  } else if (key == bindings.moveLeft) {
    keys[MOVE_LEFT] = status;
  } else if (key == bindings.moveUp) {
    keys[MOVE_UP] = status;
  } else if (key == bindings.moveDown) {
    keys[MOVE_DOWN] = status;
  } else if (key == bindings.lookUp) {
    keys[LOOK_UP] = status;
  } else if (key == bindings.lookRight) {
    keys[LOOK_RIGHT] = status;
  } else if (key == bindings.lookDown) {
    keys[LOOK_DOWN] = status;
  } else if (key == bindings.lookLeft) {
    keys[LOOK_LEFT] = status;
  }
}

void CamControlFlyMouseless::onKeyDown(const Game::Event::Ptr event) {
  Input::KeyDown::Ptr keyEvent = Game::castEvent<Input::KeyDown>(event);
  if (!keyEvent->repeat) {
    setKey(keyEvent->key, true);
  }
}

void CamControlFlyMouseless::onKeyUp(const Game::Event::Ptr event) {
  setKey(Game::castEvent<Input::KeyUp>(event)->key, false);
}
