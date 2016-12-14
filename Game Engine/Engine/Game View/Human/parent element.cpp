//
//  parent element.cpp
//  Game Engine
//
//  Created by Indi Kernick on 13/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "parent element.hpp"

void ParentElement::addChild(Element::Ptr child) {
  assert(child->parent == nullptr);
  child->parent = this;
  children.push_back(child);
  childOrderChanged = true;
}

void ParentElement::remChild(Element::Ptr child) {
  assert(child->parent == this);
  child->parent = nullptr;
  children.remove(child);
}

void ParentElement::checkOrderChange() {
  if (childOrderChanged) {
    childOrderChanged = false;
    children.sort([](auto a, auto b) {
      return a->order < b->order;
    });
  }
}
