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
) : down (down  ? down  : defaultObserver),
    up   (up    ? up    : defaultObserver),
    enter(enter ? enter : defaultObserver),
    leave(leave ? leave : defaultObserver) {}

void UI::NotifyButtonChange::operator()(const StateElement::StateChange::Ptr stateChange) const {
  if (stateChange->fromState.buttonState == stateChange->toState.buttonState) {
    return;
  }

  #define CASE(from, to) case Utils::combine(StateElement::ButtonState::from, StateElement::ButtonState::to)
  #define DOWN() down(stateChange->element); break
  #define UP() up(stateChange->element); break
  #define ENTER() enter(stateChange->element); break
  #define LEAVE() leave(stateChange->element); break
  #define IMPOSSIBLE() assert(false); break;
  
  switch (Utils::combine(stateChange->fromState.buttonState, stateChange->toState.buttonState)) {
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

void UI::NotifySubStateChange::operator()(const StateElement::StateChange::Ptr stateChange) const {
  if (
    stateChange->fromState.subState != stateChange->toState.subState &&
    stateChange->toState.subState < observers.size()
  ) {
    observers[stateChange->toState.subState](stateChange->element);
  }
}

void UI::SetTextures::operator()(const StateElement::StateChange::Ptr stateChange) const {
  if (stateChange->toState.subState < textures.size() / NUM_TEX_PER_STATE) {
    const size_t base = stateChange->toState.subState * NUM_TEX_PER_STATE;
    switch (stateChange->toState.buttonState) {
      case StateElement::ButtonState::DOWN_OUT:
      case StateElement::ButtonState::OUT:
        stateChange->element.setTexture(textures[base]);
        break;
      case StateElement::ButtonState::HOVER:
        stateChange->element.setTexture(textures[base + 1]);
        break;
      case StateElement::ButtonState::DOWN:
        stateChange->element.setTexture(textures[base + 2]);
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

void UI::SetTexturesButtonState::operator()(const StateElement::StateChange::Ptr stateChange) const {
  switch (stateChange->toState.buttonState) {
    case StateElement::ButtonState::DOWN_OUT:
    case StateElement::ButtonState::OUT:
      stateChange->element.setTexture(out);
      break;
    case StateElement::ButtonState::HOVER:
      stateChange->element.setTexture(hover);
      break;
    case StateElement::ButtonState::DOWN:
      stateChange->element.setTexture(down);
  }
}

void UI::SetTexturesSubState::operator()(const StateElement::StateChange::Ptr stateChange) const {
  if (stateChange->toState.subState < textures.size()) {
    stateChange->element.setTexture(textures[stateChange->toState.subState]);
  }
}
