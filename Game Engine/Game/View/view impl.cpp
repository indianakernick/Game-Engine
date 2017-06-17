//
//  view impl.cpp
//  Game Engine
//
//  Created by Indi Kernick on 16/6/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "view impl.hpp"

/*void Game::ViewImpl::init() {
  PROFILE(ViewImpl init);
  
  Game::HumanView::init();
  
  Platform::Window::Desc windowDesc;
  windowDesc.title = "Electric Sim";
  windowDesc.size = {1280, 720};
  windowDesc.resizable = false;
  window = app->windowManager->openWindow(windowDesc);
  renderWindow = Platform::createRenderWindow(window, app->root.get());
  scene = app->root->createSceneManager(Ogre::ST_GENERIC);
  
  camera = scene->createCamera("Main Camera");
  
  viewport = renderWindow->addViewport(camera);
  viewport->setBackgroundColour(Ogre::ColourValue(0, 0, 0));
  
  camera->setAspectRatio(
    static_cast<Ogre::Real>(viewport->getActualWidth()) /
    viewport->getActualHeight()
  );
  camera->setAutoAspectRatio(true);
  
  
}*/
