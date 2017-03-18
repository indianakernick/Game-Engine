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
    PROFILE(Main loop);
    update(delta.get());
    {
      PROFILE(Pre-render);
      renderer->preRender();
    }
    render();
    {
      PROFILE(Post-render);
      renderer->postRender();
    }
  }
  unRegisterQuitListener();
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
  quitID = evtMan->addListener(Input::Quit::TYPE, [this] (const Event::Ptr) {
    LOG_DEBUG(APPLICATION, "Game::App received quit event");
    willQuit = true;
  });
}

void Game::App::unRegisterQuitListener() {
  evtMan->remListener(Input::Quit::TYPE, quitID);
}

const std::string &Game::App::getSaveDir() {
  return saveDir;
}

void Game::App::setSaveDir() {
  saveDir = library->getSaveDir(getCompany(), getAppName());
}
