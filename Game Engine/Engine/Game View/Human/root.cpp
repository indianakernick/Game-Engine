//
//  root.cpp
//  Game Engine
//
//  Created by Indi Kernick on 11/3/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "root.hpp"

void UI::Root::setChild(Element::Ptr newChild) {
  assert(newChild);
  assert(!newChild->hasParent());
  child = newChild;
}

void UI::Root::unSetChild() {
  child = nullptr;
}

UI::Element::Ptr UI::Root::getChild() const {
  return child;
}

bool UI::Root::hasChild() const {
  return child != nullptr;
}
