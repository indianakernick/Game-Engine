//
//  base.cpp
//  Game Engine
//
//  Created by Indi Kernick on 10/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "base.hpp"

Game::HumanView::HumanView()
  : scene(std::make_shared<Scene::Root>()),
    #ifdef USE_OPENGL
    sceneRenderer(std::make_shared<Graphics3D::RendererOpenGL>())
    #endif
    {}

void Game::HumanView::init() {
  scene->restore();
  sceneRenderer->init();
}

void Game::HumanView::update(uint64_t delta) {
  processManager.update(delta);
  scene->update(delta);
}

void Game::HumanView::render() {
  sceneRenderer->render(scene);
}

void Game::HumanView::quit() {
  sceneRenderer->quit();
}

Game::View::Type Game::HumanView::getType() {
  return HUMAN;
}

Scene::Root::Ptr Game::HumanView::getScene() const {
  return scene;
}

bool Game::HumanView::onEvent(const Input::Event::Ptr) {
  return false;
}
