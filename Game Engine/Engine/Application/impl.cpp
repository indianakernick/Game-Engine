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
  
  scene = std::make_shared<Scene::Root>();
  sceneRenderer = std::make_shared<Scene::RendererOpenGL>();
  sceneRenderer->init();
  strings = std::make_shared<Strings>("en");
  
  Resource::ID duck("Meshes/duck.obj");
  glm::mat4 mat = glm::translate({}, glm::vec3(0.0f, -4.0f, 0.0f));
  mat = glm::scale(mat, glm::vec3(4.0f, 4.0f, 4.0f));
  Scene::Mesh::Ptr mesh = std::make_shared<Scene::Mesh>(73, mat, duck);
  
  camera = std::make_shared<Scene::Camera>(0xDEADBEEF, glm::mat4());
  
  mat = glm::translate({}, glm::vec3(0.0f, 5.0f, 10.0f));
  Scene::Light::CommonProps props;
  props.type = Scene::Light::SPHERE;
  props.color = {1.0f, 1.0f, 1.0f};
  props.intensity = 70.0f;
  Scene::Light::Ptr light = std::make_shared<Scene::Light>(42, mat, props);
  
  scene->addChild(mesh);
  scene->addChild(camera);
  scene->addChild(light);
  scene->setActiveCamera(0xDEADBEEF);
  
  camControl = std::make_shared<CamControlFlyMouseless>(glm::vec3(0.0f, 0.0f, 8.0f));
  input->addListener(camControl);
  
  LOG_INFO(APPLICATION, "Init took %llums", stopWatch.stop());
}

void Game::AppImpl::update(uint64_t delta) {
  input->update();
  scene->update(delta);
  camControl->update(delta);
  camera->setToWorld(camControl->getToWorld());
  
  renderer->preRender();
  sceneRenderer->render(scene);
  renderer->postRender();
  
  interval.wait();
}

void Game::AppImpl::quit() {
  Time::StopWatch<std::chrono::milliseconds> stopWatch;
  stopWatch.start();

  sceneRenderer->quit();
  quitWindow();
  library->quit();
  library.reset();
  
  LOG_INFO(APPLICATION, "Quit took %llums", stopWatch.stop());
  
  Log::quit();
}

std::string Game::AppImpl::getCompany() {
  return "Indi Kernick";
}

std::string Game::AppImpl::getAppName() {
  return "Game Engine";
}
