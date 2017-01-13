//
//  root.cpp
//  Game Engine
//
//  Created by Indi Kernick on 13/1/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "root.hpp"

Scene::Root::Root()
  : node(std::make_shared<Node>()) {}

void Scene::Root::restore() const {
  node->restore();
}

void Scene::Root::update(uint64_t delta) const {
  node->update(delta);
}

bool Scene::Root::hasChildren() const {
  return node->hasChildren();
}

size_t Scene::Root::numChildren() const {
  return node->numChildren();
}

const Scene::Node::Children &Scene::Root::getChildren() const {
  return node->getChildren();
}

Scene::Node::Ptr Scene::Root::getNode(Game::Actor::ID actor) const {
  auto iter = nodeMap.find(actor);
  if (iter != nodeMap.end()) {
    return iter->second;
  } else {
    LOG_WARNING(SCENE_GRAPH,
      "Tried to get node %llu but it was not found",
      actor);
    return nullptr;
  }
}

void Scene::Root::addChildTo(Game::Actor::ID actor, Node::Ptr child) {
  auto iter = nodeMap.find(actor);
  if (iter != nodeMap.end()) {
    nodeMap.insert({child->getActorID(), child});
    iter->second->addChild(child);
  } else {
    LOG_ERROR(SCENE_GRAPH,
      "Tried to add child %llu to %llu but the parent was not found",
      child->getActorID(), actor);
  }
}

void Scene::Root::addChild(Node::Ptr child) {
  nodeMap.insert({child->getActorID(), child});
  node->addChild(child);
}

void Scene::Root::remChild(Game::Actor::ID actor) {
  auto iter = nodeMap.find(actor);
  if (iter != nodeMap.end()) {
    iter->second->remSelf();
    nodeMap.erase(iter);
  } else {
    LOG_ERROR(SCENE_GRAPH,
      "Tried to remove child %llu but it was not found",
      actor);
  }
}

Scene::Node::Ptr Scene::Root::detachChild(Game::Actor::ID actor) {
  auto iter = nodeMap.find(actor);
  if (iter != nodeMap.end()) {
    Node::Ptr reference = iter->second;
    reference->remSelf();
    nodeMap.erase(iter);
    return reference;
  } else {
    LOG_ERROR(SCENE_GRAPH,
      "Tried to detach child %llu but it was not found",
      actor);
    return nullptr;
  }
}

void Scene::Root::setActiveCamera(Game::Actor::ID actor) {
  auto iter = nodeMap.find(actor);
  if (iter != nodeMap.end()) {
    activeCamera = iter->second;
  } else {
    activeCamera = nullptr;
    LOG_ERROR(SCENE_GRAPH,
      "Tried to set active camera to %llu but it was not found",
      actor);
  }
}

Scene::Node::Ptr Scene::Root::getActiveCamera() const {
  if (activeCamera == nullptr) {
    LOG_WARNING(SCENE_GRAPH, "Tried to get active camera but it was not set");
  }
  return activeCamera;
}
