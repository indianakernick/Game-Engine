//
//  impl.cpp
//  Game Engine
//
//  Created by Indi Kernick on 5/1/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "impl.hpp"

Game::AppImpl::AppImpl()
  : interval(16'666) {}

void Game::AppImpl::init() {
  using namespace Math::Literals;

  Time::StopWatch<std::chrono::milliseconds> stopWatch;
  stopWatch.start();

  library = std::make_shared<Libraries::SDL>();
  library->init();
  setSaveDir();
  
  Log::init((getSaveDir() + "log.txt").c_str());

  Window::Desc window;
  window.title = "Game Engine";
  window.size = {1280, 720};
  window.resizable = false;
  window.fullscreen = false;
  
  Renderer::Desc renderer;
  renderer.clearColor = {1.0, 0.0, 0.0, 1.0};
  
  initWindow(window, renderer);
  
  eventManager = std::make_shared<EventManager>();
  //init logic
  Global::resCache = std::make_shared<Resource::Cache>(50_mb);
  Global::resCache->addLoader(std::make_shared<Resource::Loaders::XML>());
  Global::resCache->addLoader(std::make_shared<Resource::Loaders::TextureOpenGL>());
  Global::resCache->addLoader(std::make_shared<Resource::Loaders::MeshOpenGL>());
  Global::resCache->addLoader(std::make_shared<Resource::Loaders::ShaderOpenGL>());
  
  scene = std::make_shared<Graphics3D::Scene>();
  strings = std::make_shared<Strings>("en");
  
  LOG_INFO(APPLICATION, "Init took %ims", stopWatch.stop());
}

void Game::AppImpl::update(uint64_t delta) {
  input->update();
  scene->update(delta);
  
  renderer->preRender();
  scene->render();
  renderer->postRender();
  
  interval.wait();
}

void Game::AppImpl::quit() {
  quitWindow();
  library->quit();
  library.reset();
  Log::quit();
}

std::string Game::AppImpl::getCompany() {
  return "Indi Kernick";
}

std::string Game::AppImpl::getAppName() {
  return "Game Engine";
}
