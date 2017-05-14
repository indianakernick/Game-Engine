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

UI::Radio::CallListeners::CallListeners(
  const Listener &unCheck,
  const Listener &check
) : unCheck(unCheck ? unCheck : defaultListener),
    check(check ? check : defaultListener) {}

void UI::Radio::CallListeners::operator()(Radio &radio, State fromState, State toState) const {
  if (fromState == toState) {
    return;
  }
         if (!isChecked(fromState) && isChecked(toState)) {
    check(radio);
  } else if (isChecked(fromState) && !isChecked(toState)) {
    unCheck(radio);
  }
}

UI::Radio::SetTextures::SetTextures(
  StringRef unCheckOut,
  StringRef unCheckHover,
  StringRef unCheckDown,
  StringRef checkOut,
  StringRef checkHover,
  StringRef checkDown
) : unCheckOut(unCheckOut),
    unCheckHover(unCheckHover),
    unCheckDown(unCheckDown),
    checkOut(checkOut),
    checkHover(checkHover),
    checkDown(checkDown) {}

void UI::Radio::SetTextures::operator()(Radio &radio, State, State toState) const {
  switch (toState) {
    case State::UNCHECK_DOWN_OUT:
    case State::UNCHECK_OUT:
      radio.setTexture(unCheckOut);
      break;
    case State::UNCHECK_HOVER:
      radio.setTexture(unCheckHover);
      break;
    case State::UNCHECK_DOWN:
      radio.setTexture(unCheckDown);
      break;
    
    case State::CHECK_DOWN_OUT:
    case State::CHECK_OUT:
      radio.setTexture(checkOut);
      break;
    case State::CHECK_HOVER:
      radio.setTexture(checkHover);
      break;
    case State::CHECK_DOWN:
      radio.setTexture(checkDown);
  };
}

void UI::Radio::onStateChange(const ChangeListener &listener) {
  stateChange = listener ? listener : defaultListener;
  stateChange(*this, state, state);
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
  stateChange(*this, state, newState);
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
