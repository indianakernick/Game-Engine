//
//  radio.cpp
//  Game Engine
//
//  Created by Indi Kernick on 27/5/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "radio.hpp"

namespace {
  bool isChecked(UI::StateElement::State state) {
    return state.subState == UI::Radio::CHECKED_STATE;
  }
  bool isUnchecked(UI::StateElement::State state) {
    return state.subState == UI::Radio::UNCHECKED_STATE;
  }

  void radioObserver(
    UI::StateElement &radio,
    UI::StateElement::State fromState,
    UI::StateElement::State toState
  ) {
    if (isUnchecked(fromState) && isChecked(toState)) {
      if (radio.hasParent()) {
        const UI::Element::Children &children = radio.getParent().getChildren();
        for (auto c = children.begin(); c != children.end(); ++c) {
          const UI::Radio::Ptr child = std::dynamic_pointer_cast<UI::Radio>(*c);
          if (child && child.get() != &radio && child->isChecked()) {
            child->uncheck();
          }
        }
      }
    }
  }
  
  bool radioConfirmer(
    const UI::StateElement &,
    UI::StateElement::State fromState,
    UI::StateElement::State toState,
    bool manual
  ) {
    //once enabled, a radio cannot be disabled. It can only be disabled if another
    //radio in the same group is enabled. So this condition says that a radio can
    //be enabled by the user and disabled by code.
    return (isChecked  (fromState) == isChecked  (toState)          ) ||
           (isUnchecked(fromState) && isChecked  (toState)          ) ||
           (isChecked  (fromState) && isUnchecked(toState) && manual);
  }
}

UI::Radio::Radio(const std::string &id, bool checked)
  : StaticStateElement(id, checked ? CHECKED_STATE : UNCHECKED_STATE) {
  addObserver(radioObserver);
  addConfirmer(radioConfirmer);
}

bool UI::Radio::isChecked() const {
  return getSubState() == CHECKED_STATE;
}

bool UI::Radio::isUnchecked() const {
  return getSubState() == UNCHECKED_STATE;
}

void UI::Radio::check() {
  setSubState(CHECKED_STATE);
}

void UI::Radio::uncheck() {
  setSubState(UNCHECKED_STATE);
}
