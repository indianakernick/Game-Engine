//
//  button.cpp
//  Game Engine
//
//  Created by Indi Kernick on 4/3/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "button.hpp"

void UI::Button::onDown(Listener listener) {
  down = listener;
}

void UI::Button::onUp(Listener listener) {
  up = listener;
}

void UI::Button::onEnter(Listener listener) {
  enter = listener;
}

void UI::Button::onLeave(Listener listener) {
  leave = listener;
}

void UI::Button::setTextures(const Textures &newTextures) {
  textures = newTextures;
}

const UI::Button::Textures &UI::Button::getTextures() const {
  return textures;
}

const Res::ID &UI::Button::getTexture() const {
  switch (state) {
    case DEFAULT:
      return textures.def;
    case HOVER:
      return textures.hover;
    case DOWN:
      return textures.down;
  }
}

void UI::Button::changeState(State newState) {
  if (state == newState) {
    return;
  }
  
  switch (combine(state, newState)) {
    case combine(DEFAULT, DOWN):
    case combine(HOVER, DOWN):
      down(this);
      break;
    case combine(DEFAULT, HOVER):
      enter(this);
      break;
    case combine(HOVER, DEFAULT):
      leave(this);
      break;
    case combine(DOWN, DEFAULT):
    case combine(DOWN, HOVER):
      up(this);
  }
  
  state = newState;
}
