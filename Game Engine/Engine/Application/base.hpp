//
//  base.hpp
//  Game Engine
//
//  Created by Indi Kernick on 14/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_application_base_hpp
#define engine_application_base_hpp

#include "../Platform/Interface/window library.hpp"
#include "../Platform/Interface/system info.hpp"
#include "../Game Logic/base.hpp"
#include "../Time/delta.hpp"
#include "../Utils/profiler.hpp"
#include "../Event/manager.hpp"
#include "../Resource/Managers/texture atlas.hpp"

namespace Game {
  class App {
  public:
    App() = default;
    virtual ~App() = default;
    
    void mainloop();
    
    const std::string &getSaveDir() const;
    const std::string &getResDir() const;
    
    Logic::Ptr gameLogic;
    Platform::InputManager::Ptr inputManager;
    Platform::WindowManager::Ptr windowManager;
    std::unique_ptr<Ogre::Root> root;
    
  private:
    std::string saveDir;
    std::string resDir;
    EventManager::ListenerID quitID;
    bool willQuit = false;
    
    std::unique_ptr<Res::TextureAtlasManager> textureAtlasManager;
    
    void initApp();
    void updateApp(uint64_t);
    void quitApp();
    void setResourceLocations();
    void createResourceManagers();
    void destroyResourceManagers();
    void registerQuitListener();
    void unRegisterQuitListener();
    
    virtual void init() = 0;
    virtual void update(uint64_t) = 0;
    virtual void quit() = 0;
    
    virtual std::string getCompany() const = 0;
    virtual std::string getAppName() const = 0;
    virtual std::string getPluginFile() const = 0;
    virtual std::string getConfigFile() const = 0;
    virtual std::string getResourceFile() const = 0;
  };
}

extern std::unique_ptr<Game::App> app;

#endif
