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
  } else {
    if (child->parent != nullptr) {
      LOG_ERROR(SCENE_GRAPH,
        "Tried to add child %llu to %llu but it already had a parent",
        child->actor, actor);
    }
    child->parent = this;
  }
}

void Scene::Node::remChild(Node::Ptr child) {
  if (child == nullptr) {
    LOG_ERROR(SCENE_GRAPH,
      "Tried to remove child from %llu but that node is null",
      actor);
    return;
  } else if (child->parent == nullptr) {
    LOG_ERROR(SCENE_GRAPH,
      "Tried to remove child %llu from %llu but that node doesn't have a parent",
      child->actor, actor);
    return;
  } else if (child->parent != this) {
    LOG_ERROR(SCENE_GRAPH,
      "Tried to remove child %llu from %llu but that node is not a child of this node",
      child->actor, actor);
    return;
  }
  
  size_t sizeBefore = children.size();
  children.remove(child);
  if (sizeBefore == children.size()) {
    LOG_WARNING(SCENE_GRAPH,
      "Tried to remove child %llu from %llu but child was not found",
      child->actor, actor);
  } else {
    child->parent = nullptr;
  }
}

void Scene::Node::remChild(Game::Actor::ID child) {
  if (child == Game::Actor::NULL_ID) {
    LOG_ERROR(SCENE_GRAPH,
      "Tried to remove child from %llu but the ID was null",
      actor);
    return;
  }

  size_t sizeBefore = children.size();
  children.remove_if([childActor = child, this](Node::Ptr &child) {
    if (child->actor == childActor) {
      if (child->parent == nullptr) {
        LOG_ERROR(SCENE_GRAPH,
          "Tried to remove child %llu from %llu but that node doesn't have a parent",
          childActor, actor);
      } else if (child->parent != this) {
        LOG_ERROR(SCENE_GRAPH,
          "Tried to remove child %llu from %llu but that node is not a child of this node",
          childActor, actor);
      }
      return true;
    } else {
      return false;
    }
  });
  if (sizeBefore == children.size()) {
    LOG_WARNING(SCENE_GRAPH,
      "Tried to remove child %llu from %llu but child was not found",
      child, actor);
  }
}

void Scene::Node::remSelf() {
  if (parent) {
    parent->children.remove_if([this](Node::Ptr &sibling) {
      return sibling.get() == this;
    });
    parent = nullptr;
  } else {
    LOG_WARNING(SCENE_GRAPH,
      "Tried to remove self %llu but this node has no parent",
      actor);
  }
}

Scene::Node::Ptr Scene::Node::detachChild(Game::Actor::ID child) {
  for (auto i = children.begin(); i != children.end(); ++i) {
    if ((*i)->actor == child) {
      Node::Ptr ptr = *i;
      children.erase(i);
      
      if (ptr->parent != this) {
        LOG_ERROR(SCENE_GRAPH,
          "Tried to detach child %llu from %llu but that node's parent is not this node",
          child, actor);
      }
      
      ptr->parent = nullptr;
      return ptr;
    }
  }
  LOG_ERROR(SCENE_GRAPH,
    "Tried to detach child %llu from %llu but child was not found",
    child, actor);
  return nullptr;
}

void Scene::Node::setToWorld(const glm::mat4 &mat) {
  toWorld = mat;
  fromWorld = glm::inverse(toWorld);
}

void Scene::Node::setFromWorld(const glm::mat4 &mat) {
  fromWorld = mat;
  toWorld = glm::inverse(fromWorld);
}

const glm::mat4 &Scene::Node::getToWorld() const {
  return toWorld;
}

const glm::mat4 &Scene::Node::getFromWorld() const {
  return fromWorld;
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
