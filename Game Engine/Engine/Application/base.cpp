//
//  base.cpp
//  Game Engine
//
//  Created by Indi Kernick on 14/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "base.hpp"

std::unique_ptr<Game::App> app = nullptr;

void Game::App::mainloop() {
  initApp();
  Time::Delta<std::chrono::milliseconds> delta;
  willQuit = false;
  while (!willQuit) {
    PROFILE(Main loop);
    updateApp(delta.get());
  }
  quitApp();
}

const std::string &Game::App::getSaveDir() const {
  return saveDir;
}

const std::string &Game::App::getResDir() const {
  return resDir;
}

void Game::App::initApp() {
  saveDir = Platform::getSaveDir(getCompany(), getAppName());
  resDir = Platform::getResDir();
  Utils::Log::init((saveDir + "engine.log").c_str());
  Platform::initLib();
  evtMan = std::make_unique<Game::EventManager>(8'000'000);
  windowManager = Platform::createWindowManager();
  inputManager = Platform::createInputManager(windowManager);
  registerQuitListener();
  root = std::make_unique<Ogre::Root>(
    getPluginFile(),
    getConfigFile(),
    saveDir + "ogre.log"
  );
  createResourceManagers();
  setResourceLocations();
  init();
}

void Game::App::updateApp(uint64_t delta) {
  inputManager->update();
  update(delta);
  root->renderOneFrame();
}

void Game::App::quitApp() {
  quit();
  destroyResourceManagers();
  root.reset();
  inputManager.reset();
  windowManager.reset();
  evtMan.reset();
  Platform::quitLib();
  Utils::Log::quit();
}

void Game::App::setResourceLocations() {
  Ogre::ConfigFile config;
  config.load(getResourceFile());
  
  Ogre::ResourceGroupManager &resMan = Ogre::ResourceGroupManager::getSingleton();
  Ogre::ConfigFile::SectionIterator secIter = config.getSectionIterator();
  while (secIter.hasMoreElements()) {
    Ogre::ConfigFile::SettingsMultiMap *settings = secIter.getNext();
    for (auto i = settings->begin(); i != settings->end(); i++) {
      resMan.addResourceLocation(resDir + i->second, i->first);
    }
  }
}

void Game::App::createResourceManagers() {
  textureAtlasManager = std::make_unique<Res::TextureAtlasManager>();
  uiScreenManager = std::make_unique<Res::UIScreenManager>();
  xmlManager = std::make_unique<Res::XMLManager>();
}

void Game::App::destroyResourceManagers() {
  xmlManager.reset();
  uiScreenManager.reset();
  textureAtlasManager.reset();
}

void Game::App::registerQuitListener() {
  quitID = evtMan->addListener([this] (const Input::Quit::Ptr) {
    LOG_DEBUG(APPLICATION, "Game::App received quit event");
    willQuit = true;
    unRegisterQuitListener();
  });
}

void Game::App::unRegisterQuitListener() {
  evtMan->remListener(quitID);
}
