//
//  view impl.cpp
//  Game Engine
//
//  Created by Indi Kernick on 16/6/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "view impl.hpp"

void Game::ViewImpl::init() {
  PROFILE(Game::ViewImpl::init);
  
  Game::HumanView::init();
  
  Platform::Window::Desc windowDesc;
  windowDesc.title = "Electric Sim";
  windowDesc.size = {1280, 720};
  windowDesc.resizable = true;
  window = app->windowManager->openWindow(windowDesc);
  renderWindow = Platform::createRenderWindow(window, app->root.get());
  scene = app->root->createSceneManager(Ogre::ST_GENERIC);
  
  camera = scene->createCamera("Main Camera");
  camera->setPosition(0, 0, 5);
  camera->lookAt(0, 0, 0);
  camera->setNearClipDistance(5);
  
  viewport = renderWindow->addViewport(camera);
  viewport->setBackgroundColour(Ogre::ColourValue(0, 0, 0));
  camera->setAspectRatio(
    static_cast<Ogre::Real>(viewport->getActualWidth()) /
    viewport->getActualHeight()
  );
  camera->setAutoAspectRatio(true);
  
  Res::UIScreen::Ptr uiScreen = Res::UIScreenManager::getSingleton().load(
    "electric_sim.xml",
    Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME
  ).dynamicCast<Res::UIScreen>();
  uiRoot = std::make_unique<UI::Root>(window, viewport, scene);
  uiRoot->setChild(uiScreen->getRoot(), uiScreen->getMaterialName(), uiScreen->getAtlasName());
}

void Game::ViewImpl::update(const uint64_t delta) {
  PROFILE(Game::ViewImpl::update);
  
  HumanView::update(delta);
}

void Game::ViewImpl::quit() {
  PROFILE(Game::ViewImpl::quit);
  
  HumanView::quit();
}
