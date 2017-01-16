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
  auto iter = nodes.find(actor);
  if (iter != nodes.end()) {
    return iter->second;
  } else {
    LOG_WARNING(SCENE_GRAPH,
      "Tried to get node %llu but it was not found",
      actor);
    return nullptr;
  }
}

void Scene::Root::addChildTo(Game::Actor::ID actor, Node::Ptr child) {
  auto iter = nodes.find(actor);
  if (iter != nodes.end()) {
    nodes.insert({child->getActorID(), child});
    iter->second->addChild(child);
    std::shared_ptr<Light> light = std::dynamic_pointer_cast<Light>(child);
    if (light) {
      lights.push_back(light);
    }
  } else {
    LOG_ERROR(SCENE_GRAPH,
      "Tried to add child %llu to %llu but the parent was not found",
      child->getActorID(), actor);
  }
}

void Scene::Root::addChild(Node::Ptr child) {
  nodes.insert({child->getActorID(), child});
  node->addChild(child);
  std::shared_ptr<Light> light = std::dynamic_pointer_cast<Light>(child);
  if (light) {
    lights.push_back(light);
  }
}

void Scene::Root::remChild(Game::Actor::ID actor) {
  if (actor == Game::Actor::NULL_ID) {
    LOG_ERROR(SCENE_GRAPH,
      "Tried to remove child but the ID was null");
    return;
  }

  auto iter = nodes.find(actor);
  if (iter != nodes.end()) {
    Node::Ptr child = iter->second;
    node->remChild(child);
    nodes.erase(iter);
    std::shared_ptr<Light> light = std::dynamic_pointer_cast<Light>(child);
    if (light) {
      size_t sizeBefore = lights.size();
      lights.remove(light);
      if (sizeBefore == lights.size()) {
        LOG_WARNING(SCENE_GRAPH,
          "Tried to remove light %llu but it was not found",
          actor);
      }
    }
  } else {
    LOG_WARNING(SCENE_GRAPH,
      "Tried to remove child %llu but it was not found",
      actor);
  }
}

Scene::Node::Ptr Scene::Root::detachChild(Game::Actor::ID actor) {
  auto iter = nodes.find(actor);
  if (iter != nodes.end()) {
    Node::Ptr reference = node->detachChild(actor);
    nodes.erase(iter);
    return reference;
  } else {
    LOG_ERROR(SCENE_GRAPH,
      "Tried to detach child %llu but it was not found",
      actor);
    return nullptr;
  }
}

void Scene::Root::setActiveCamera(Game::Actor::ID actor) {
  auto iter = nodes.find(actor);
  if (iter != nodes.end()) {
    if (iter->second) {
      std::shared_ptr<Scene::Camera> camera =
        std::dynamic_pointer_cast<Scene::Camera>(iter->second);
      if (camera) {
        activeCamera = camera;
        return;
      } else {
        LOG_ERROR(SCENE_GRAPH,
          "Tried to set active camera to %llu but that node is not a camera",
          actor);
      }
    } else {
      LOG_ERROR(SCENE_GRAPH,
        "Tried to set active camera to %llu but that node is null",
        actor);
    }
  } else {
    LOG_ERROR(SCENE_GRAPH,
      "Tried to set active camera to %llu but it was not found",
      actor);
  }
  activeCamera = nullptr;
}

std::shared_ptr<Scene::Camera> Scene::Root::getActiveCamera() const {
  if (activeCamera == nullptr) {
    LOG_WARNING(SCENE_GRAPH, "Tried to get active camera but it was not set");
  }
  return activeCamera;
}

const Scene::Root::Lights &Scene::Root::getLights() const {
  return lights;
}

const Scene::Root::Nodes &Scene::Root::getNodes() const {
  return nodes;
}
