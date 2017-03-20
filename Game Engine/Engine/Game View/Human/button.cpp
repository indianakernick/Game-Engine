//
//  button.cpp
//  Game Engine
//
//  Created by Indi Kernick on 4/3/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "button.hpp"

void UI::Button::onDown(const Listener &listener) {
  setListener<&Button::down>(listener);
}

void UI::Button::onUp(const Listener &listener) {
  setListener<&Button::up>(listener);
}

void UI::Button::onEnter(const Listener &listener) {
  setListener<&Button::enter>(listener);
}

void UI::Button::onLeave(const Listener &listener) {
  setListener<&Button::leave>(listener);
}

void UI::Button::setTextures(const Textures &newTextures) {
  textures = newTextures;
}

const UI::Button::Textures &UI::Button::getTextures() const {
  return textures;
}

const Res::ID &UI::Button::getTexture() const {
  switch (state) {
    case State::DOWN_OUT:
    case State::OUT:
      return textures.out;
    case State::HOVER:
      return textures.hover;
    case State::DOWN:
      return textures.down;
  }
}

template <UI::Button::Listener UI::Button::*MEMBER>
void UI::Button::setListener(const Listener &listener) {
  if (listener) {
    this->*MEMBER = listener;
  } else {
    this->*MEMBER = defaultListener;
  }
}

void UI::Button::changeState(State newState) {
  assert(state != newState);
  
  #define CASE(state, newState) case combine(State::state, State::newState)
  #define DOWN() down(*this); break
  #define UP() up(*this); break
  #define ENTER() enter(*this); break
  #define LEAVE() leave(*this); break
  #define IMPOSSIBLE() assert(false)
  
  switch (combine(state, newState)) {
    CASE(DOWN_OUT, OUT):
      UP();
    CASE(DOWN_OUT, HOVER):
      IMPOSSIBLE();
    CASE(DOWN_OUT, DOWN):
      ENTER();
    
    CASE(OUT, DOWN_OUT):
      IMPOSSIBLE();
    CASE(OUT, HOVER):
      ENTER();
    CASE(OUT, DOWN):
      IMPOSSIBLE();
    
    CASE(HOVER, DOWN_OUT):
      IMPOSSIBLE();
    CASE(HOVER, OUT):
      LEAVE();
    CASE(HOVER, DOWN):
      DOWN();
    
    CASE(DOWN, DOWN_OUT):
      LEAVE();
    CASE(DOWN, OUT):
      IMPOSSIBLE();
    CASE(DOWN, HOVER):
      UP();
    
    default:
      IMPOSSIBLE();
  }
  
  #undef IMPOSSIBLE
  #undef LEAVE
  #undef ENTER
  #undef UP
  #undef DOWN
  #undef CASE
  
  state = newState;
}

void UI::Button::onMouseDown() {
  changeState(State::DOWN);
}

void UI::Button::onMouseUp(bool within) {
  if (within) {
    changeState(State::HOVER);
  } else {
    changeState(State::OUT);
  }
}

void UI::Button::onMouseEnter(bool mouseDown) {
  if (mouseDown) {
    changeState(State::DOWN);
  } else {
    changeState(State::HOVER);
  }
}

void UI::Button::onMouseLeave(bool mouseDown) {
  if (mouseDown) {
    changeState(State::DOWN_OUT);
  } else {
    changeState(State::OUT);
  }
}
