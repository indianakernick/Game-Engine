//
//  checkbox.cpp
//  Game Engine
//
//  Created by Indi Kernick on 20/3/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "checkbox.hpp"

void UI::Checkbox::onCheck(const Listener &listener) {
  setListener<&Checkbox::check>(listener);
}

void UI::Checkbox::onUncheck(const Listener &listener) {
  setListener<&Checkbox::uncheck>(listener);
}

void UI::Checkbox::setTextures(const Textures &newTextures) {
  textures = newTextures;
}

const UI::Checkbox::Textures &UI::Checkbox::getTextures() const {
  return textures;
}

const Res::ID &UI::Checkbox::getTexture() const {
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
  }
}

template <UI::Checkbox::Listener UI::Checkbox::*MEMBER>
void UI::Checkbox::setListener(const Listener &listener) {
  if (listener) {
    this->*MEMBER = listener;
  } else {
    this->*MEMBER = defaultListener;
  }
}

bool UI::Checkbox::isChecked(State state) {
  return state >= State::CHECK_DOWN_OUT;
}

UI::Checkbox::State UI::Checkbox::makeCheckedIf(bool cond, State state) {
  return static_cast<State>(
    static_cast<uint8_t>(state) |
    (static_cast<uint8_t>(cond) << 2)
  );
  
  /*
  about 35% faster than this
  
  if (cond) {
    if (isChecked(state)) {
      return state;
    } else {
      return static_cast<State>(static_cast<uint8_t>(state) + 4);
    }
  } else {
    return state;
  }
  */
}

void UI::Checkbox::changeState(State newState) {
  assert(state != newState);
  
         if (!isChecked(state) && isChecked(newState)) {
    check(*this);
  } else if (isChecked(state) && !isChecked(newState)) {
    uncheck(*this);
  }
  
  state = newState;
}

void UI::Checkbox::onMouseDown() {
  changeState(makeCheckedIf(!isChecked(state), State::UNCHECK_DOWN));
}

void UI::Checkbox::onMouseUp(bool within) {
  if (within) {
    changeState(makeCheckedIf(isChecked(state), State::UNCHECK_HOVER));
  } else {
    changeState(makeCheckedIf(isChecked(state), State::UNCHECK_OUT));
  }
}

void UI::Checkbox::onMouseEnter(bool mouseDown) {
  if (mouseDown) {
    changeState(makeCheckedIf(isChecked(state), State::UNCHECK_DOWN));
  } else {
    changeState(makeCheckedIf(isChecked(state), State::UNCHECK_HOVER));
  }
}

void UI::Checkbox::onMouseLeave(bool mouseDown) {
  if (mouseDown) {
    changeState(makeCheckedIf(isChecked(state), State::UNCHECK_DOWN_OUT));
  } else {
    changeState(makeCheckedIf(isChecked(state), State::UNCHECK_OUT));
  }
}
