//
//  impl.cpp
//  Game Engine
//
//  Created by Indi Kernick on 24/1/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "impl.hpp"

void Game::HumanViewImpl::init() {
  Game::HumanView::init();
  
  Resource::ID duck("Meshes/nightwing anim.dae");
  anim = new Graphics3D::Anim(duck);
  anim->play(0);
  anim->loop();
  
  glm::mat4 mat = glm::translate({}, glm::vec3(0.0f, -21.0f, 0.0f));
  mat = glm::rotate(mat, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
  mat = glm::scale(mat, glm::vec3(1000.0f, 1000.0f, 1000.0f));
  Scene::Mesh::Ptr mesh = std::make_shared<Scene::Mesh>(73, mat, duck);
  
  camera = std::make_shared<Scene::Camera>(0xDEADBEEF, glm::mat4());
  Speed speed;
  speed.move = 25.0f;
  speed.vert = 25.0f;
  speed.look = 1.0f;
  controller = std::make_shared<CamControlFlyMouseless>(Bindings(),speed,glm::vec3(0.0f, 0.0f, 100.0f));
  
  mat = glm::translate({}, glm::vec3(0.0f, 30.0f, 25.0f));
  Scene::Light::CommonProps props;
  props.type = Scene::Light::SPHERE;
  props.color = {1.0f, 1.0f, 1.0f};
  props.intensity = 600.0f;
  Scene::Light::Ptr light = std::make_shared<Scene::Light>(42, mat, props);
  
  scene->addChild(mesh);
  scene->addChild(camera);
  scene->addChild(light);
  scene->setActiveCamera(0xDEADBEEF);
  
  app->input->addListener(controller);
}

void Game::HumanViewImpl::update(uint64_t delta) {
  HumanView::update(delta);
  anim->update(delta);
  controller->update(delta);
  camera->setToWorld(controller->getToWorld());
}

void Game::HumanViewImpl::quit() {
  HumanView::quit();
  delete anim;
}
