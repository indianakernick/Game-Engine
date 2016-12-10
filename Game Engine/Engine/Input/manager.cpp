//
//  manager.cpp
//  Game Engine
//
//  Created by Indi Kernick on 4/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "manager.hpp"

void Input::Manager::addQuitHandler(QuitHandler handler) {
  quitHandlers.push_front(handler);
}

void Input::Manager::remQuitHandler(QuitHandler handler) {
  quitHandlers.remove_if([&handler] (const QuitHandler &current) {
    return current.target<QuitHandler>() == handler.target<QuitHandler>();
  });
}

void Input::Manager::addMouseHandler(MouseHandler::Ptr handler) {
  if (handler->manager) {
    throw std::runtime_error("Mouse handler cannot be attached to more than one Manager");
  }
  handler->manager = this;
  mouseHandlers.push_front(handler);
}

void Input::Manager::remMouseHandler(MouseHandler::Ptr handler) {
  handler->manager = nullptr;
  mouseHandlers.remove(handler);
}

void Input::Manager::addKeyboardHandler(KeyboardHandler::Ptr handler) {
  if (handler->manager) {
    throw std::runtime_error("Keyboard handler cannot be attached to more than one Manager");
  }
  handler->manager = this;
  keyboardHandlers.push_front(handler);
}

void Input::Manager::remKeyboardHandler(KeyboardHandler::Ptr handler) {
  handler->manager = nullptr;
  keyboardHandlers.remove(handler);
}

void Input::Manager::quit() {
  for (auto i = quitHandlers.begin(); i != quitHandlers.end(); ++i) {
    (*i)();
  }
  mouseHandlers.clear();
  keyboardHandlers.clear();
}

void Input::Manager::mouseMovedAbs(Geometry::Point newPos) {
  Geometry::Point delta = newPos - mousePos;
  mousePos = newPos;
  mouseEvent(&MouseHandler::onMove, newPos, delta);
}

void Input::Manager::mouseMovedRel(Geometry::Point delta) {
  Geometry::Point newPos = mousePos + delta;
  mousePos = newPos;
  mouseEvent(&MouseHandler::onMove, newPos, delta);
}

void Input::Manager::mouseScroll(Geometry::Point delta) {
  mouseEvent(&MouseHandler::onScroll, mousePos, delta);
}

void Input::Manager::mouseDown(MButton::Type button) {
  mouseState[button] = true;
  mouseEvent(&MouseHandler::onDown, mousePos, button);
}

void Input::Manager::mouseUp(MButton::Type button) {
  mouseState[button] = false;
  mouseEvent(&MouseHandler::onUp, mousePos, button);
}

void Input::Manager::keyDown(Key::Type key) {
  keyState[key] = true;
  keyEvent(&KeyboardHandler::onDown, key, getModifiers(keyState));
}

void Input::Manager::keyUp(Key::Type key) {
  keyState[key] = false;
  keyEvent(&KeyboardHandler::onUp, key, getModifiers(keyState));
}

void Input::Manager::setMouseCapture(MouseHandler *handler) {
  mouseCapture = handler;
}

void Input::Manager::setKeyboardFocus(KeyboardHandler *handler) {
  keyboardFocus = handler;
}
