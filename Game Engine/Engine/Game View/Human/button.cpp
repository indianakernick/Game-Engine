//
//  button.cpp
//  Game Engine
//
//  Created by Indi Kernick on 4/3/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "button.hpp"

UI::Button::CallListeners::CallListeners(
  const Listener &down,
  const Listener &up,
  const Listener &enter,
  const Listener &leave
) : down (down  ? down  : defaultListener),
    up   (up    ? up    : defaultListener),
    enter(enter ? enter : defaultListener),
    leave(leave ? leave : defaultListener) {}

void UI::Button::CallListeners::operator()(
  Button &button,
  State fromState,
  State toState
) {
  if (fromState == toState) {
    return;
  }

  #define CASE(from, to) case combine(State::from, State::to)
  #define DOWN() down(button); break
  #define UP() up(button); break
  #define ENTER() enter(button); break
  #define LEAVE() leave(button); break
  #define IMPOSSIBLE() assert(false); break;
  
  switch (combine(fromState, toState)) {
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
}

UI::Button::SetTextures::SetTextures(
  const std::string &out,
  const std::string &hover,
  const std::string &down
) : out(out),
    hover(hover),
    down(down) {}

void UI::Button::SetTextures::operator()(Button &button, State, State toState) {
  switch (toState) {
    case State::DOWN_OUT:
    case State::OUT:
      button.setTexture(out);
      break;
    case State::HOVER:
      button.setTexture(hover);
      break;
    case State::DOWN:
      button.setTexture(down);
  };
}

void UI::Button::onStateChange(const ChangeListener &listener) {
  stateChange = listener ? listener : defaultListener;
  stateChange(*this, state, state);
}

void UI::Button::changeState(State newState) {
  assert(state != newState);
  stateChange(*this, state, newState);
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
