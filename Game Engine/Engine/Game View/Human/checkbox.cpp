//
//  checkbox.cpp
//  Game Engine
//
//  Created by Indi Kernick on 20/3/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "checkbox.hpp"

UI::Checkbox::Checkbox(const std::string &id, bool checked)
  : Element(id), state(makeCheckedIf(checked, State::UNCHECK_OUT)) {}

UI::Checkbox::CallListeners::CallListeners(
  const Listener &unCheck,
  const Listener &check
) : unCheck(unCheck ? unCheck : defaultListener),
    check(check ? check : defaultListener) {}

void UI::Checkbox::CallListeners::operator()(Checkbox &checkbox, State fromState, State toState) const {
  if (fromState == toState) {
    return;
  }
         if (!isChecked(fromState) && isChecked(toState)) {
    check(checkbox);
  } else if (isChecked(fromState) && !isChecked(toState)) {
    unCheck(checkbox);
  }
}

UI::Checkbox::SetTextures::SetTextures(
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

void UI::Checkbox::SetTextures::operator()(Checkbox &checkbox, State, State toState) const {
  switch (toState) {
    case State::UNCHECK_DOWN_OUT:
    case State::UNCHECK_OUT:
      checkbox.setTexture(unCheckOut);
      break;
    case State::UNCHECK_HOVER:
      checkbox.setTexture(unCheckHover);
      break;
    case State::UNCHECK_DOWN:
      checkbox.setTexture(unCheckDown);
      break;
    
    case State::CHECK_DOWN_OUT:
    case State::CHECK_OUT:
      checkbox.setTexture(checkOut);
      break;
    case State::CHECK_HOVER:
      checkbox.setTexture(checkHover);
      break;
    case State::CHECK_DOWN:
      checkbox.setTexture(checkDown);
  };
}

UI::Checkbox::ListenerID UI::Checkbox::addStateChangeListener(const Listener &listener) {
  const ListenerID id = stateChange.addListener(listener);
  stateChange.notify(*this, state, state);
  return id;
}

void UI::Checkbox::remStateChangeListener(ListenerID id) {
  stateChange.remListener(id);
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
  stateChange.notify(*this, state, newState);
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
