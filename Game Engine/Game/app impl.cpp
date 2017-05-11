//
//  app impl.cpp
//  Game Engine
//
//  Created by Indi Kernick on 5/1/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "app impl.hpp"

void Game::AppImpl::init() {
  PROFILE(AppImpl init);
  
  if (!root->restoreConfig()) {
    if (!root->showConfigDialog()) {
      std::exit(0);
    }
    root->saveConfig();
  }
  root->initialise(false);
  
  Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
  Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
  
  gameLogic = std::make_shared<Game::LogicImpl>();
  gameLogic->attachView(std::make_shared<Game::HumanViewImpl>(), 1);
  
  gameLogic->init();
}

void Game::AppImpl::update(uint64_t delta) {
  PROFILE(AppImpl update);
  
  evtMan->update();
  gameLogic->update(delta);
  Logic::Views &views = gameLogic->getViews();
  for (auto v = views.begin(); v != views.end(); ++v) {
    v->second->update(delta);
  }
}

void Game::AppImpl::quit() {
  PROFILE(AppImpl quit);

  gameLogic->quit();
  evtMan.reset();
}

std::string Game::AppImpl::getCompany() const {
  return "Indi Kernick";
}

std::string Game::AppImpl::getAppName() const {
  return "Game Engine";
}

std::string Game::AppImpl::getPluginFile() const {
  return getResDir() + "ogre plugins.cfg";
}

std::string Game::AppImpl::getConfigFile() const {
  return getSaveDir() + "ogre.cfg";
}

std::string Game::AppImpl::getResourceFile() const {
  return getResDir() + "ogre resources.cfg";
}
