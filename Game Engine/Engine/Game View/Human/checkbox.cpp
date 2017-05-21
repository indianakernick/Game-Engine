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

bool UI::Checkbox::CallListeners::operator()(Checkbox &checkbox, State fromState, State toState, bool) const {
  if (fromState == toState) {
    return true;
  }
         if (!isChecked(fromState) && isChecked(toState)) {
    check(checkbox);
  } else if (isChecked(fromState) && !isChecked(toState)) {
    unCheck(checkbox);
  }
  
  return true;
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

bool UI::Checkbox::SetTextures::operator()(Checkbox &checkbox, State, State toState, bool) const {
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
  
  return true;
}

bool UI::Checkbox::Radio::operator()(Checkbox &checkbox, State fromState, State toState, bool manual) const {
  if (!isChecked(fromState) && isChecked(toState)) {
    if (checkbox.hasParent()) {
      const Children &children = checkbox.getParent().getChildren();
      for (auto c = children.begin(); c != children.end(); ++c) {
        const Checkbox::Ptr child = std::dynamic_pointer_cast<Checkbox>(*c);
        if (child && child.get() != &checkbox && isChecked(child->state)) {
          child->uncheck();
        }
      }
    }
  } else if (isChecked(fromState) && !isChecked(toState) && !manual) {
    return false;
  }
  return true;
}

UI::Checkbox::ListenerID UI::Checkbox::addStateChangeListener(const Listener &listener) {
  const ListenerID id = stateChange.addListener(listener);
  stateChange.notify(*this, state, state, true);
  return id;
}

void UI::Checkbox::remStateChangeListener(ListenerID id) {
  stateChange.remListener(id);
}

bool UI::Checkbox::isChecked() const {
  return isChecked(state);
}

void UI::Checkbox::check() {
  if (!isChecked()) {
    changeState(makeChecked(state), true);
  }
}

void UI::Checkbox::uncheck() {
  if (isChecked()) {
    changeState(makeUnchecked(state), true);
  }
}

bool UI::Checkbox::isChecked(State state) {
  return state >= State::CHECK_DOWN_OUT;
}

UI::Checkbox::State UI::Checkbox::makeCheckedIf(bool cond, State state) {
  return static_cast<State>(
    static_cast<uint8_t>(state) |
    (static_cast<uint8_t>(cond) << static_cast<uint8_t>(2))
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

UI::Checkbox::State UI::Checkbox::makeChecked(State state) {
  return static_cast<State>(
    static_cast<uint8_t>(state) |
    static_cast<uint8_t>(4)
  );
}

UI::Checkbox::State UI::Checkbox::makeUnchecked(State state) {
  return static_cast<State>(
    static_cast<uint8_t>(state) &
    static_cast<uint8_t>(3)
  );
}

void UI::Checkbox::changeState(State newState, bool manual) {
  if (state != newState) {
    if (stateChange.notify(*this, state, newState, manual)) {
      state = newState;
    } else {
      stateChange.notify(*this, newState, state, true);
    }
  }
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
