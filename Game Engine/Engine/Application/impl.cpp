//
//  impl.cpp
//  Game Engine
//
//  Created by Indi Kernick on 5/1/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "impl.hpp"

Game::AppImpl::AppImpl() {}

void Game::AppImpl::init() {
  using namespace Math::Literals;
  
  PROFILE(AppImpl init);

  Time::StopWatch<std::chrono::milliseconds> stopWatch;
  stopWatch.start();
  Platform::initLib();
  setSaveDir();
  
  Log::init((getSaveDir() + "log.txt").c_str());

  //event manager never takes longer that 8 milliseconds to process events
  evtMan = std::make_unique<Game::EventManager>(8'000'000);

  Platform::Window::Desc window;
  window.title = "Game Engine";
  window.size = {1280, 720};
  window.resizable = false;
  window.fullscreen = false;
  
  initWindow(window);
  std::string resDir = Platform::getResDir();
  std::string saveDir = getSaveDir();
  root = std::make_unique<Ogre::Root>(
    resDir + "ogre plugins.cfg",
    saveDir + "ogre.cfg",
    saveDir + "ogre.log"
  );
  Ogre::ConfigFile config;
  config.load(resDir + "ogre resources.cfg");
  
  Ogre::ConfigFile::SectionIterator secIter = config.getSectionIterator();
  while (secIter.hasMoreElements()) {
    Ogre::ConfigFile::SettingsMultiMap *settings = secIter.getNext();
    for (auto i = settings->begin(); i != settings->end(); i++) {//  name                location type
      Ogre::ResourceGroupManager::getSingleton().addResourceLocation(resDir + i->second, i->first);
    }
  }
  
  if (!root->restoreConfig()) {
    if (!root->showConfigDialog()) {
      std::exit(1);
    }
    root->saveConfig();
  }
  root->initialise(false);
  
  Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
  Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
  
  gameLogic = std::make_shared<Game::LogicImpl>();
  gameLogic->attachView(std::make_shared<Game::HumanViewImpl>(), 1);
  
  gameLogic->init();
  
  LOG_INFO(APPLICATION, "Init took %llums", stopWatch.stop());
}

void Game::AppImpl::update(uint64_t delta) {
  PROFILE(AppImpl update);
  
  input->update();
  evtMan->update();
  gameLogic->update(delta);
  Logic::Views &views = gameLogic->getViews();
  for (auto v = views.begin(); v != views.end(); ++v) {
    v->second->update(delta);
  }
}

void Game::AppImpl::quit() {
  PROFILE(AppImpl quit);

  Time::StopWatch<std::chrono::milliseconds> stopWatch;
  stopWatch.start();
  
  gameLogic->quit();
  quitWindow();
  Platform::quitLib();
  evtMan.reset();
  
  LOG_INFO(APPLICATION, "Quit took %llums", stopWatch.stop());
  
  Log::quit();
}

std::string Game::AppImpl::getCompany() {
  return "Indi Kernick";
}

std::string Game::AppImpl::getAppName() {
  return "Game Engine";
}
