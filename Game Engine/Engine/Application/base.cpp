//
//  base.cpp
//  Game Engine
//
//  Created by Indi Kernick on 14/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "base.hpp"

#ifdef _SDL_H

void Game::App::initWindow(const Window::Desc &winDesc, const Renderer::Desc &renDesc) {
  library = std::make_shared<Libraries::SDL>();
  library->init();
  window = std::make_shared<Windows::SDLOpenGL>();
  window->open(winDesc);
  renderer = window->createRenderer(renDesc);
  input = window->createInputManager();
}

#endif

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
