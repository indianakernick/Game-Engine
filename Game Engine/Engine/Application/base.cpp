//
//  base.cpp
//  Game Engine
//
//  Created by Indi Kernick on 14/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "base.hpp"

void Game::App::initWindow(Library::Ptr lib, const Window::Desc &winDesc, const Renderer::Desc &renDesc) {
  library = lib;
  library->init();
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
  library->quit();
  library.reset();
}

std::string Game::App::getSaveDir() {
  return library->getSaveDir(getCompany(), getAppName());
}
