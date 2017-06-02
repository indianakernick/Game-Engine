//
//  state element.cpp
//  Game Engine
//
//  Created by Indi Kernick on 24/5/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "state element.hpp"

bool UI::StateElement::State::operator==(const State other) const {
  return buttonState == other.buttonState && subState == other.subState;
}

bool UI::StateElement::State::operator!=(const State other) const {
  return buttonState != other.buttonState || subState != other.subState;
}

UI::StateElement::StateError::StateError(const char *what)
  : std::runtime_error(what) {}

UI::StateElement::StateElement(const std::string &id, SubState numSubStates, SubState initSubState)
  : Element(id), state({ButtonState::OUT, initSubState}), numSubStates(numSubStates) {
  if (initSubState >= numSubStates) {
    throw StateError("Invalid initial sub state");
  }
}

UI::StateElement::ObserverID UI::StateElement::addObserver(const Observer &observer) {
  const ObserverID id = stateChangeNotif.addListener(observer);
  stateChangeNotif.dispatch(*this, state, state);
  return id;
}

void UI::StateElement::remObserver(ObserverID id) {
  stateChangeNotif.remListener(id);
}

UI::StateElement::ConfirmerID UI::StateElement::addConfirmer(const Confirmer &confirmer) {
  return stateChangeConfirm.addListener(confirmer);
}

void UI::StateElement::remConfirmer(ConfirmerID id) {
  stateChangeConfirm.remListener(id);
}

void UI::StateElement::setDecider(const Decider &newDecider) {
  decider = newDecider ? newDecider : defaultDecider;
}

void UI::StateElement::setDefaultDecider() {
  decider = defaultDecider;
}

void UI::StateElement::setNoChangeDecider() {
  decider = noChangeDecider;
}

void UI::StateElement::setSubState(SubState newSubState) {
  if (newSubState >= numSubStates) {
    throw StateError("Sub state set to invalid value");
  }
  changeSubState(newSubState, true);
}

UI::StateElement::SubState UI::StateElement::getSubState() const {
  return state.subState;
}

void UI::StateElement::changeButtonState(ButtonState newButtonState) {
  changeState({newButtonState, state.subState}, false);
}

void UI::StateElement::changeSubState(SubState newSubState, bool manual) {
  changeState({state.buttonState, newSubState}, manual);
}

void UI::StateElement::changeState(State newState, bool manual) {
  if (state != newState) {
    if (stateChangeConfirm.dispatch(*this, state, newState, manual)) {
      stateChangeNotif.dispatch(*this, state, newState);
      state = newState;
    }
  }
}

UI::StateElement::SubState UI::StateElement::nextSubState() const {
  const SubState newSubState = decider(state.subState, numSubStates);
  if (newSubState >= numSubStates) {
    throw StateError("Decider returned invalid state");
  }
  return newSubState;
}

UI::StateElement::SubState UI::StateElement::defaultDecider(SubState state, SubState numStates) {
  return (state + 1) % numStates;
}

UI::StateElement::SubState UI::StateElement::noChangeDecider(SubState state, SubState) {
  return state;
}

void UI::StateElement::onMouseDown() {
  changeState({ButtonState::DOWN, nextSubState()});
}

void UI::StateElement::onMouseUp(bool within) {
  changeButtonState(within ? ButtonState::HOVER : ButtonState::OUT);
}

void UI::StateElement::onMouseEnter(bool mouseDown) {
  changeButtonState(mouseDown ? ButtonState::DOWN : ButtonState::HOVER);
}

void UI::StateElement::onMouseLeave(bool mouseDown) {
  changeButtonState(mouseDown ? ButtonState::DOWN_OUT : ButtonState::OUT);
}
