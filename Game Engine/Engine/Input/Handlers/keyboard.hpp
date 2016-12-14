//
//  keyboard.hpp
//  Game Engine
//
//  Created by Indi Kernick on 4/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_input_handlers_keyboard_hpp
#define engine_input_handlers_keyboard_hpp

#include "../State/keyboard.hpp"
#include <memory>

namespace Input {
  class Manager;
  
  namespace Handlers {
    class Keyboard {
    friend class ::Input::Manager;
    public:
      using Ptr = std::shared_ptr<Keyboard>;
    
      Keyboard() = default;
      virtual ~Keyboard() = default;
      
      //returning true means that the event was handled and no other handlers
      //need to see it
      virtual bool onDown(Key::Type, Mod::Type) = 0;
      virtual bool onUp(Key::Type, Mod::Type) = 0;
    protected:
      void focusOn();
      void focusOff();
    private:
      Manager *manager = nullptr;
    };
  }
};

#include "../manager.hpp"

#endif
