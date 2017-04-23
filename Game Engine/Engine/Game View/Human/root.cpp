//
//  root.cpp
//  Game Engine
//
//  Created by Indi Kernick on 11/3/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "root.hpp"

UI::Root::Root(
  const Ogre::String &name,
  std::weak_ptr<Platform::Window> window,
  Ogre::Viewport *viewport,
  Ogre::SceneManager *sceneManager)
  : input(window), renderer(name, window, viewport, sceneManager) {}

void UI::Root::setChild(Element::Ptr newChild) {
  assert(newChild);
  assert(!newChild->hasParent());
  child = newChild;
  input.setRoot(child);
  renderer.setRoot(child);
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
