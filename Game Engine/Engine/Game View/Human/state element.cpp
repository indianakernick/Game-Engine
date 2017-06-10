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

UI::StateElement::StateChange::StateChange(
  StateElement &element,
  const State fromState,
  const State toState,
  const bool manual
) : element(element),
    fromState(fromState),
    toState(toState),
    manual(manual) {}

UI::StateElement::StateError::StateError(const char *what)
  : std::runtime_error(what) {}

UI::StateElement::StateElement(const std::string &id, SubState numSubStates, SubState initSubState)
  : Element(id), state({ButtonState::OUT, initSubState}), numSubStates(numSubStates) {
  if (initSubState >= numSubStates) {
    throw StateError("Invalid initial sub state");
  }
  
  addListener(Utils::memFunWrap(this, &StateElement::onMouseDown));
  addListener(Utils::memFunWrap(this, &StateElement::onMouseUp));
  addListener(Utils::memFunWrap(this, &StateElement::onMouseEnter));
  addListener(Utils::memFunWrap(this, &StateElement::onMouseLeave));
}

UI::StateElement::ListenerID UI::StateElement::addEventListener(
  const Event::Type type,
  const Listener &listener
) {
  if (type == GetEventType<StateChange>::get()) {
    const StateChange::Ptr stateChange = std::make_shared<StateChange>(
      *this,
      state,
      state,
      true
    );
    listener(stateChange);
  }
  return Element::addEventListener(type, listener);
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
    const StateChange::Ptr stateChange = std::make_shared<StateChange>(*this, state, newState, manual);
    if (stateChangeConfirm.dispatch(stateChange)) {
      dispatchEvent(stateChange);
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

void UI::StateElement::onMouseDown(const MouseDown::Ptr) {
  changeState({ButtonState::DOWN, nextSubState()});
}

void UI::StateElement::onMouseUp(const MouseUp::Ptr mouseUp) {
  changeButtonState(mouseUp->within ? ButtonState::HOVER : ButtonState::OUT);
}

void UI::StateElement::onMouseEnter(const MouseEnter::Ptr mouseEnter) {
  changeButtonState(mouseEnter->down ? ButtonState::DOWN : ButtonState::HOVER);
}

void UI::StateElement::onMouseLeave(const MouseLeave::Ptr mouseLeave) {
  changeButtonState(mouseLeave->down ? ButtonState::DOWN_OUT : ButtonState::OUT);
}
