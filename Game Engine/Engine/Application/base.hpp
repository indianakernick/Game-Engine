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
#include "../Game Logic/base.hpp"
#include "../Resource/cache.hpp"
#include "../Math/byteconstants.hpp"
#include "../Time/delta.hpp"
#include "../Resource/Handles/strings.hpp"
#include "../Utils/profiler.hpp"
#include "../Event/manager.hpp"

namespace Game {
  class App {
  public:
    App() = default;
    virtual ~App() = default;
    
    virtual void init() = 0;
    void mainloop();
    virtual void update(uint64_t) = 0;
    virtual void render() = 0;
    virtual void quit() = 0;
    
    void initWindow(const Platform::Window::Desc &,
                    const Platform::RenderingContext::Desc &);
    void quitWindow();
    
    virtual std::string getCompany() = 0;
    virtual std::string getAppName() = 0;
    
    void registerQuitListener();
    void unRegisterQuitListener();
    
    const std::string &getSaveDir();
    
    Logic::Ptr gameLogic;
    Res::Strings::Ptr strings;
    
    Platform::Window::Ptr window;
    Platform::RenderingContext::Ptr renderer;
    Platform::InputManager::Ptr input;
  protected:
    void setSaveDir();
  private:
    std::string saveDir;
    EventManager::ListenerID quitID;
    bool willQuit = false;
  };
}

extern std::unique_ptr<Game::App> app;

#endif
