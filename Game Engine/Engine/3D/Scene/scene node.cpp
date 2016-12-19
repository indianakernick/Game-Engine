//
//  scene node.cpp
//  Game Engine
//
//  Created by Indi Kernick on 18/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "scene node.hpp"

Graphics3D::SceneNode::SceneNode(Game::Actor::ID actor,
                                 RenderPass pass,
                                 const Material &material,
                                 const glm::mat4 &toWorld,
                                 float radius)
 : prop(actor, pass, material, toWorld, radius) {}

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

bool Graphics3D::SceneNode::isVisible(Scene *scene) const {
  return scene->getCamera()->getFrustum().inside(prop.toWorld[3], prop.radius);
}

void Graphics3D::SceneNode::preRender(Scene *scene) {
  scene->pushMat(prop.toWorld);
}

void Graphics3D::SceneNode::renderChildren(Scene *scene) {
  for (auto i = children.begin(); i != children.end(); ++i) {
    SceneNode::Ptr child = *i;
    if (child == nullptr) {
      continue;
    }
    child->preRender(scene);
    if (child->isVisible(scene)) {
      float alpha = child->prop.material.getAlpha();
      if (alpha == 1.0f) {
        child->render(scene);
      } else if (alpha > 0.0f) {
        renderAlpha(scene, child);
      }
    }
    (*i)->renderChildren(scene);
    (*i)->postRender(scene);
  }
}

void Graphics3D::SceneNode::postRender(Scene *scene) {
  scene->popMat();
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

void Graphics3D::SceneNode::renderAlpha(Scene *scene, SceneNode::Ptr child) {
  AlphaSceneNode alphaNode;
  alphaNode.node = child;
  alphaNode.toWorld = scene->topMat();
  
  glm::vec4 worldPos = alphaNode.toWorld[3];
  glm::mat4 toCamera = scene->getCamera()->prop.fromWorld;
  glm::vec3 screenPos = worldPos * toCamera;
  alphaNode.depth = screenPos.z;
  
  scene->pushAlphaNode(alphaNode);
}
