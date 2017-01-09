//
//  scene node.cpp
//  Game Engine
//
//  Created by Indi Kernick on 18/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "scene node.hpp"

#include "camera node.hpp"

Graphics3D::SceneNode::SceneNode(Game::Actor::ID actor,
                                 RenderPass pass,
                                 const glm::mat4 &toWorld,
                                 float radius)
 : prop(actor, pass, toWorld, radius) {}

const Graphics3D::NodeProperties &Graphics3D::SceneNode::getProp() const {
  return prop;
}

void Graphics3D::SceneNode::setTransform(const glm::mat4 &toWorld,
                                         const glm::mat4 &fromWorld) {
  prop.toWorld = toWorld;
  prop.fromWorld = fromWorld;
}

void Graphics3D::SceneNode::setToWorld(const glm::mat4 &toWorld) {
  prop.toWorld = toWorld;
  prop.fromWorld = glm::inverse(toWorld);
}

void Graphics3D::SceneNode::setFromWorld(const glm::mat4 &fromWorld) {
  prop.fromWorld = fromWorld;
  prop.toWorld = glm::inverse(fromWorld);
}

void Graphics3D::SceneNode::restore(Scene *scene) {
  for (auto i = children.begin(); i != children.end(); ++i) {
    if (*i) {
      (*i)->restore(scene);
    }
  }
}

void Graphics3D::SceneNode::update(Scene *scene, uint64_t delta) {
  for (auto i = children.begin(); i != children.end(); ++i) {
    if (*i) {
      (*i)->update(scene, delta);
    }
  }
}

bool Graphics3D::SceneNode::isVisible(CameraNode::Ptr camera) const {
  return camera->getFrustum().inside(prop.toWorld[3], prop.radius);
}

void Graphics3D::SceneNode::preRender(MatStack &stack) {
  stack.push(prop.toWorld);
}

void Graphics3D::SceneNode::render(MatStack &stack, Program3D *program, CameraNode::Ptr camera) {
  renderChildren(stack, program, camera);
}

void Graphics3D::SceneNode::renderChildren(MatStack &stack, Program3D *program, CameraNode::Ptr camera) {
  for (auto i = children.begin(); i != children.end(); ++i) {
    SceneNode::Ptr child = *i;
    if (child == nullptr) {
      continue;
    }
    child->preRender(stack);
    if (child->isVisible(camera)) {
      child->render(stack, program, camera);
    }
    (*i)->renderChildren(stack, program, camera);
    (*i)->postRender(stack);
  }
}

void Graphics3D::SceneNode::postRender(MatStack &stack) {
  stack.pop();
}

void Graphics3D::SceneNode::addChild(SceneNode::Ptr node) {
  children.push_back(node);
  node->parent = this;
  
  glm::vec3 nodePos = node->prop.toWorld[3];
  glm::vec3 thisPos = prop.toWorld[3];
  
  glm::vec3 thisToNode = nodePos - thisPos;
  float newRadius = thisToNode.length() + node->prop.radius;
  if (newRadius > prop.radius) {
    prop.radius = newRadius;
  }
}

void Graphics3D::SceneNode::remChild(Game::Actor::ID actor) {
  for (auto i = children.begin(); i != children.end(); ++i) {
    if (*i && (*i)->prop.actor == actor) {
      *i = nullptr;
      //assume there are no duplicates
      return;
    }
  }
  LOG_WARNING(SCENE_GRAPH, "Tried to removed child from node but it was not removed");
}

void Graphics3D::SceneNode::remSelf() const {
  if (parent) {
    parent->remChild(prop.actor);
  } else {
    throw std::runtime_error("Failed to remove self from parent: don't have a parent");
  }
}

Graphics3D::SceneNode::Ptr Graphics3D::SceneNode::detachChild(Game::Actor::ID actor) {
  for (auto i = children.begin(); i != children.end(); ++i) {
    if (*i && (*i)->prop.actor == actor) {
      //ensure we have at least one reference so that the node isnt deleted
      //when we set it to null
      SceneNode::Ptr copy = *i;
      *i = nullptr;
      return copy;
    }
  }
  LOG_WARNING(SCENE_GRAPH, "Tried to detach child from node but it was not detached");
  return nullptr;
}

size_t Graphics3D::SceneNode::countNullChildren() const {
  size_t count = 0;
  for (auto i = children.begin(); i != children.end(); ++i) {
    if (*i == nullptr) {
      count++;
    }
  }
  return count;
}
