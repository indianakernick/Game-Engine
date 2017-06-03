//
//  draggable.cpp
//  Game Engine
//
//  Created by Indi Kernick on 28/5/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "draggable.hpp"

UI::Draggable::Draggable(const std::string &id)
  : StaticStateElement(id) {
  addListener(MouseMove::TYPE, memFun(this, &Draggable::onMouseMove));
}

void UI::Draggable::onMouseMove(const Event::Ptr event) {
  const MouseMove::Ptr mouseMove = safeDownCast<MouseMove>(event);
  if (mouseMove->down) {
    if (bounds.posSpace() == Space::REL) {
      bounds.pos(bounds.pos() + mouseMove->relParDelta);
    } else { //bounds.posSpace() == Space::ABS
      bounds.pos(bounds.pos() + mouseMove->absDelta);
    }
  }
}
