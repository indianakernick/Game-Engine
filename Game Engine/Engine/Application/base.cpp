//
//  base.cpp
//  Game Engine
//
//  Created by Indi Kernick on 14/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "base.hpp"

Game::App *app = nullptr;

void Game::App::mainloop() {
  init();
  willQuit = false;
  registerQuitListener();
  Time::Delta<std::chrono::milliseconds> delta;
  while (!willQuit) {
    update(delta.get());
  }
  quit();
}

void Game::App::initWindow(const Window::Desc &winDesc, const Renderer::Desc &renDesc) {
  window = library->makeWindow();
  window->open(winDesc);
  renderer = window->createRenderer(renDesc);
  input = window->createInputManager();
}

void Game::App::quitWindow() {
  input.reset();
  renderer->quit();
  renderer.reset();
  window->close();
  window.reset();
}

void Game::App::registerQuitListener() {
  input->addQuitListener([this] {
    LOG_DEBUG(APPLICATION, "Game::App received quit event");
    willQuit = true;
  });
}

const std::string &Game::App::getSaveDir() {
  return saveDir;
}


void Game::App::setSaveDir() {
  saveDir = library->getSaveDir(getCompany(), getAppName());
}
