//
//  checkbox.cpp
//  Game Engine
//
//  Created by Indi Kernick on 20/3/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "checkbox.hpp"

UI::Checkbox::Checkbox(const std::string &id, bool checked)
  : StaticStateElement(id, checked ? CHECKED_STATE : UNCHECKED_STATE) {}

bool UI::Checkbox::isChecked() const {
  return getSubState() == CHECKED_STATE;
}

bool UI::Checkbox::isUnchecked() const {
  return getSubState() == UNCHECKED_STATE;
}

void UI::Checkbox::check() {
  setSubState(CHECKED_STATE);
}

void UI::Checkbox::uncheck() {
  setSubState(UNCHECKED_STATE);
}
