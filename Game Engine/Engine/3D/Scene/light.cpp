//
//  light.cpp
//  Game Engine
//
//  Created by Indi Kernick on 13/1/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "light.hpp"

Scene::Light::Light(Game::Actor::ID actor,
                    const glm::mat4 &toWorld,
                    const CommonProps &props)
  : Node(actor, toWorld), props(props) {
  assert(props.type == DIRECT || props.type == SPHERE);
}

Scene::Light::Light(Game::Actor::ID actor,
                    const glm::mat4 &toWorld,
                    const CommonProps &props,
                    float angle)
  : Node(actor, toWorld), props(props), angle(angle) {
  assert(props.type == CIRC_SPOT);
}

Scene::Light::Light(Game::Actor::ID actor,
                    const glm::mat4 &toWorld,
                    const CommonProps &props,
                    Angles angle2)
  : Node(actor, toWorld),
    props(props),
    horiAngle(angle2.hori),
    vertAngle(angle2.vert) {
  assert(props.type == RECT_SPOT);
}

Scene::Light::AllProps Scene::Light::getAllProps() const {
  AllProps allProps;
  allProps.type = props.type;
  allProps.color = props.color;
  allProps.intensity = props.intensity;
  allProps.horiAngle = horiAngle;
  allProps.vertAngle = vertAngle;
  return allProps;
}

Scene::Light::Type Scene::Light::getType() const {
  return props.type;
}

const glm::vec3 &Scene::Light::getColor() const {
  return props.color;
}

float Scene::Light::getIntensity() const {
  return props.intensity;
}

float Scene::Light::getAngle() const {
  assert(props.type == CIRC_SPOT);
  return angle;
}

Scene::Light::Angles Scene::Light::getAngle2() const {
  assert(props.type == RECT_SPOT);
  return {horiAngle, vertAngle};
}

void Scene::Light::setColor(const glm::vec3 &color) {
  props.color = color;
}

void Scene::Light::setIntensity(float intensity) {
  props.intensity = intensity;
}

void Scene::Light::setAngle(float angle) {
  assert(props.type == CIRC_SPOT);
  this->angle = angle;
}

void Scene::Light::setAngle2(Angles angles) {
  assert(props.type == RECT_SPOT);
  horiAngle = angles.hori;
  vertAngle = angles.vert;
}
