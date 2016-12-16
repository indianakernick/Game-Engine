//
//  base.hpp
//  Game Engine
//
//  Created by Indi Kernick on 14/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_application_base_hpp
#define engine_application_base_hpp

#include "library.hpp"
#include "../Memory/buffer.hpp"
#include "../Game Logic/base.hpp"
#include "../Resource/cache.hpp"
#include "../Math/byteconstants.hpp"
#include "window.hpp"

#ifdef _SDL_H

#include "Libraries/sdl.hpp"
#include "Windows/sdl opengl.hpp"

#endif

namespace Game {
  class App {
  public:
    App() = default;
    ~App() = default;
    
    virtual void init() = 0;
    virtual void quit() = 0;
    
    void initWindow(const Window::Desc &, const Renderer::Desc &);
    void quitWindow();
    
    virtual std::string getCompany();
    virtual std::string getAppName();
    
    std::string getSaveDir();
    
    EventManager::Ptr eventManager;
    Logic::Ptr gameLogic;
    Resource::Cache::Ptr cache;
    
    Library::Ptr library;
    Window::Ptr window;
    Renderer::Ptr renderer;
    Input::Manager::Ptr input;
  };
}

extern Game::App *app;

#endif
