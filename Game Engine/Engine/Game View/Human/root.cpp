//
//  root.cpp
//  Game Engine
//
//  Created by Indi Kernick on 11/3/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "root.hpp"

UI::Root::Root(
  std::weak_ptr<Platform::Window> window,
  Ogre::Viewport *viewport,
  Ogre::SceneManager *sceneManager)
  : input(window), renderer(window, viewport, sceneManager) {}

void UI::Root::setChild(
  Element::Ptr newChild,
  const std::string &matName,
  const std::string &atlasName
) {
  assert(newChild);
  assert(!newChild->hasParent());
  child = newChild;
  input.setRoot(child);
  renderer.setRoot(child, matName, atlasName);
}

void UI::Root::unSetChild() {
  child = nullptr;
  input.unSetRoot();
  renderer.unSetRoot();
}

UI::Element::Ptr UI::Root::getChild() const {
  return child;
}

bool UI::Root::hasChild() const {
  return child != nullptr;
}
