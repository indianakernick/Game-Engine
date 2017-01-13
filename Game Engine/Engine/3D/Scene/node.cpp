//
//  node.cpp
//  Game Engine
//
//  Created by Indi Kernick on 13/1/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "node.hpp"

Scene::Node::Node(Game::Actor::ID actor, const glm::mat4 &toWorld)
  : actor(actor), toWorld(toWorld) {}

void Scene::Node::restore() {
  restoreChildren();
}

void Scene::Node::update(uint64_t delta) {
  updateChildren(delta);
}

bool Scene::Node::hasParent() const {
  return parent;
}

Scene::Node *Scene::Node::getParent() const {
  return parent;
}

bool Scene::Node::hasChildren() const {
  return children.size();
}

size_t Scene::Node::numChildren() const {
  return children.size();
}

const Scene::Node::Children &Scene::Node::getChildren() const {
  return children;
}

void Scene::Node::addChild(Node::Ptr child) {
  children.push_back(child);
  if (child == nullptr) {
    LOG_WARNING(SCENE_GRAPH,
      "Tried to add child to %llu but it was null",
      actor);
  }
}

void Scene::Node::remChild(Game::Actor::ID child) {
  size_t sizeBefore = children.size();
  children.remove_if([childActor = child](Node::Ptr &child) {
    return child->actor == childActor;
  });
  if (sizeBefore == children.size()) {
    LOG_WARNING(SCENE_GRAPH,
      "Tried to remove child %llu from %llu but child was not found",
      child, actor);
  }
}

void Scene::Node::remSelf() const {
  if (parent) {
    parent->children.remove_if([this](Node::Ptr &sibling) {
      return sibling.get() == this;
    });
  } else {
    LOG_WARNING(SCENE_GRAPH,
      "Tried to remove self %llu but this node has no parent",
      actor);
  }
}

Scene::Node::Ptr Scene::Node::detachChild(Game::Actor::ID child) {
  for (auto i = children.begin(); i != children.end(); ++i) {
    if ((*i)->actor == child) {
      children.erase(i);
      return *i;
    }
  }
  LOG_WARNING(SCENE_GRAPH,
    "Tried to detach child %llu from %llu but child was not found",
    child, actor);
  return nullptr;
}

void Scene::Node::setToWorld(const glm::mat4 &mat) {
  toWorld = mat;
}

const glm::mat4 &Scene::Node::getToWorld() const {
  return toWorld;
}

Game::Actor::ID Scene::Node::getActorID() const {
  return actor;
}

void Scene::Node::restoreChildren() const {
  std::for_each(children.begin(), children.end(), [](const Node::Ptr &child) {
    child->restore();
  });
}

void Scene::Node::updateChildren(uint64_t delta) const {
  std::for_each(children.begin(), children.end(), [delta](const Node::Ptr &child) {
    child->update(delta);
  });
}
