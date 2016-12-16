//
//  base.hpp
//  Game Engine
//
//  Created by Indi Kernick on 14/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_application_base_hpp
#define engine_application_base_hpp

#include <string>
#include "../Memory/buffer.hpp"
#include "../Game Logic/base.hpp"
#include "../Resource/cache.hpp"
#include "../Math/byteconstants.hpp"

namespace Game {
  class App {
  public:
    App() = default;
    ~App() = default;
    
    virtual void init();
    virtual void quit();
    
    virtual std::string getTitle() = 0;
    virtual Memory::Buffer getIcon() = 0;
    virtual std::string getSaveDir() = 0;
    
    EventManager::Ptr eventManager;
    Logic::Ptr gameLogic;
    Resource::Cache::Ptr cache;
  };
}

extern Game::App *app;

#endif
