//
//  draggable.cpp
//  Game Engine
//
//  Created by Indi Kernick on 28/5/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "draggable.hpp"

UI::Draggable::Draggable(const std::string &id)
  : StaticStateElement(id) {}

void UI::Draggable::onMouseMove(MouseData mouseData) {
  if (mouseData.down) {
    if (bounds.posSpace() == Space::REL) {
      bounds.pos(bounds.pos() + mouseData.relParDelta);
    } else { //bounds.posSpace() == Space::ABS
      bounds.pos(bounds.pos() + mouseData.absDelta);
    }
  }
}
