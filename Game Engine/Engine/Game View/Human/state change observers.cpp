//
//  state change observers.cpp
//  Game Engine
//
//  Created by Indi Kernick on 27/5/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "state change observers.hpp"

UI::NotifyButtonChange::NotifyButtonChange(
  const Observer &down,
  const Observer &up,
  const Observer &enter,
  const Observer &leave
) : down(down ? down : defaultObserver),
    up(up ? up : defaultObserver),
    enter(enter ? enter : defaultObserver),
    leave(leave ? leave : defaultObserver) {}

void UI::NotifyButtonChange::operator()(
  StateElement &element,
  StateElement::State fromState,
  StateElement::State toState
) {
  if (fromState.buttonState == toState.buttonState) {
    return;
  }

  #define CASE(from, to) case combine(StateElement::ButtonState::from, StateElement::ButtonState::to)
  #define DOWN() down(element); break
  #define UP() up(element); break
  #define ENTER() enter(element); break
  #define LEAVE() leave(element); break
  #define IMPOSSIBLE() assert(false); break;
  
  switch (combine(fromState.buttonState, toState.buttonState)) {
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

void UI::NotifySubStateChange::operator()(
  StateElement &element,
  StateElement::State fromState,
  StateElement::State toState
) {
  if (fromState.subState != toState.subState && toState.subState < observers.size()) {
    observers[toState.subState](element);
  }
}

void UI::SetTextures::operator()(
  StateElement &stateElement,
  StateElement::State,
  StateElement::State toState
) {
  if (toState.subState < textures.size() / NUM_TEX_PER_STATE) {
    const size_t base = toState.subState * NUM_TEX_PER_STATE;
    switch (toState.buttonState) {
      case StateElement::ButtonState::DOWN_OUT:
      case StateElement::ButtonState::OUT:
        stateElement.setTexture(textures[base]);
        break;
      case StateElement::ButtonState::HOVER:
        stateElement.setTexture(textures[base + 1]);
        break;
      case StateElement::ButtonState::DOWN:
        stateElement.setTexture(textures[base + 2]);
    }
  }
}

UI::SetTexturesButtonState::SetTexturesButtonState(
  const std::string &out,
  const std::string &hover,
  const std::string &down
) : out(out),
    hover(hover),
    down(down) {}

UI::SetTexturesButtonState::SetTexturesButtonState(
  const Texture &out,
  const Texture &hover,
  const Texture &down
) : out(out),
    hover(hover),
    down(down) {}

void UI::SetTexturesButtonState::operator()(
  StateElement &element,
  StateElement::State,
  StateElement::State toState
) {
  switch (toState.buttonState) {
    case StateElement::ButtonState::DOWN_OUT:
    case StateElement::ButtonState::OUT:
      element.setTexture(out);
      break;
    case StateElement::ButtonState::HOVER:
      element.setTexture(hover);
      break;
    case StateElement::ButtonState::DOWN:
      element.setTexture(down);
  }
}

void UI::SetTexturesSubState::operator()(
  StateElement &element,
  StateElement::State,
  StateElement::State toState
) {
  if (toState.subState < textures.size()) {
    element.setTexture(textures[toState.subState]);
  }
}
