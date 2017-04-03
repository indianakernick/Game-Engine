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
  quit();
}

void Game::App::initWindow(const Platform::Window::Desc &winDesc,
                           const Platform::RenderingContext::Desc &renDesc) {
  window = Platform::openWindow(winDesc);
  renderer = Platform::createRenderingContext(window, renDesc);
  input = Platform::createInputManager(window);
}

void Game::App::quitWindow() {
  input.reset();
  renderer.reset();
  window.reset();
}

void Game::App::registerQuitListener() {
  quitID = evtMan->addListener(Input::Quit::TYPE, [this] (const Event::Ptr) {
    LOG_DEBUG(APPLICATION, "Game::App received quit event");
    willQuit = true;
    unRegisterQuitListener();
  });
}

void Game::App::unRegisterQuitListener() {
  evtMan->remListener(Input::Quit::TYPE, quitID);
}

const std::string &Game::App::getSaveDir() {
  return saveDir;
}

void Game::App::setSaveDir() {
  saveDir = Platform::getSaveDir(getCompany(), getAppName());
}
