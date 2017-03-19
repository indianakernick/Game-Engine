//
//  button.cpp
//  Game Engine
//
//  Created by Indi Kernick on 4/3/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "button.hpp"

void UI::Button::onDown(Listener listener) {
  setListener<&Button::down>(listener);
}

void UI::Button::onUp(Listener listener) {
  setListener<&Button::up>(listener);
}

void UI::Button::onEnter(Listener listener) {
  setListener<&Button::enter>(listener);
}

void UI::Button::onLeave(Listener listener) {
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
    case DOWN_OUT:
    case OUT:
      return textures.out;
    case HOVER:
      return textures.hover;
    case DOWN:
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
  changeState(DOWN);
}

void UI::Button::onMouseUp(bool within) {
  if (within) {
    changeState(HOVER);
  } else {
    changeState(OUT);
  }
}

void UI::Button::onMouseEnter(bool mouseDown) {
  if (mouseDown) {
    changeState(DOWN);
  } else {
    changeState(HOVER);
  }
}

void UI::Button::onMouseLeave(bool mouseDown) {
  if (mouseDown) {
    changeState(DOWN_OUT);
  } else {
    changeState(OUT);
  }
}
