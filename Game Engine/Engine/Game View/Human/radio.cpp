//
//  radio.cpp
//  Game Engine
//
//  Created by Indi Kernick on 25/3/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "radio.hpp"

UI::Radio::Radio(bool checked)
  : state(makeCheckedIf(checked, State::UNCHECK_OUT)) {}

void UI::Radio::onCheck(const Listener &listener) {
  setListener<&Radio::check>(listener);
}

void UI::Radio::onUncheck(const Listener &listener) {
  setListener<&Radio::uncheck>(listener);
}

void UI::Radio::setTextures(const Textures &newTextures) {
  textures = newTextures;
}

const UI::Radio::Textures &UI::Radio::getTextures() const {
  return textures;
}

const std::string &UI::Radio::getTexture() const {
  switch (state) {
    case State::UNCHECK_DOWN_OUT:
    case State::UNCHECK_OUT:
      return textures.unCheckOut;
    case State::UNCHECK_HOVER:
      return textures.unCheckHover;
    case State::UNCHECK_DOWN:
      return textures.unCheckDown;
    
    case State::CHECK_DOWN_OUT:
    case State::CHECK_OUT:
      return textures.checkOut;
    case State::CHECK_HOVER:
      return textures.checkHover;
    case State::CHECK_DOWN:
      return textures.checkDown;
  };
}

template <UI::Radio::Listener UI::Radio::*MEMBER>
void UI::Radio::setListener(const Listener &listener) {
  this->*MEMBER = listener ? listener : defaultListener;
}

bool UI::Radio::isChecked(State state) {
  return state >= State::CHECK_DOWN_OUT;
}

UI::Radio::State UI::Radio::makeCheckedIf(bool cond, State state) {
  return static_cast<State>(
    static_cast<uint8_t>(state) |
    (static_cast<uint8_t>(cond) << 2)
  );
}

UI::Radio::State UI::Radio::makeUnchecked(State state) {
  return static_cast<State>(
    static_cast<uint8_t>(state) &
    static_cast<uint8_t>(3)
  );
}

void UI::Radio::changeState(State newState) {
  assert(state != newState);
  
         if (!isChecked(state) && isChecked(newState)) {
    check(*this);
  } else if (isChecked(state) && !isChecked(newState)) {
    uncheck(*this);
  }
  
  state = newState;
}

void UI::Radio::onMouseDown() {
  if (!isChecked(state)) {
    changeState(State::CHECK_DOWN);
    
    if (parent) {
      const Children &children = parent->getChildren();
      for (auto c = children.begin(); c != children.end(); ++c) {
        const Radio::Ptr child = std::dynamic_pointer_cast<Radio>(*c);
        if (child && child.get() != this && isChecked(child->state)) {
          child->changeState(makeUnchecked(child->state));
        }
      }
    }
  }
  //do nothing if this radio is already checked
}

void UI::Radio::onMouseUp(bool within) {
  if (!isChecked(state)) {
    if (within) {
      changeState(State::UNCHECK_HOVER);
    } else {
      changeState(State::UNCHECK_OUT);
    }
  }
}

void UI::Radio::onMouseEnter(bool mouseDown) {
  if (mouseDown) {
    changeState(makeCheckedIf(isChecked(state), State::UNCHECK_DOWN));
  } else {
    changeState(makeCheckedIf(isChecked(state), State::UNCHECK_HOVER));
  }
}

void UI::Radio::onMouseLeave(bool mouseDown) {
  if (mouseDown) {
    changeState(makeCheckedIf(isChecked(state), State::UNCHECK_DOWN_OUT));
  } else {
    changeState(makeCheckedIf(isChecked(state), State::UNCHECK_OUT));
  }
}
