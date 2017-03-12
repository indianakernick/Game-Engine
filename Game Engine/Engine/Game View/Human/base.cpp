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
    ui(std::make_shared<UI::Root>()),
    #ifdef USE_OPENGL
    sceneRenderer(std::make_shared<Graphics3D::RendererOpenGL>()),
    uiRenderer(std::make_shared<UI::RendererOpenGL>())
    #endif
    {}

void Game::HumanView::init() {
  PROFILE(HumanView init);

  scene->restore();
  sceneRenderer->init();
  uiRenderer->init();
}

void Game::HumanView::update(uint64_t delta) {
  PROFILE(HumanView update);

  processManager.update(delta);
  scene->update(delta);
}

void Game::HumanView::render() {
  PROFILE(HumanView render);

  sceneRenderer->render(scene);
  uiRenderer->render(ui);
}

void Game::HumanView::quit() {
  PROFILE(HumanView quit);

  uiRenderer->quit();
  sceneRenderer->quit();
}

Game::View::Type Game::HumanView::getType() {
  return HUMAN;
}

Scene::Root::Ptr Game::HumanView::getScene() const {
  return scene;
}

UI::Root::Ptr Game::HumanView::getUI() const {
  return ui;
}

bool Game::HumanView::onEvent(const Input::Event::Ptr) {
  return false;
}
