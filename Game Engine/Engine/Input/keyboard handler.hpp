//
//  keyboard handler.hpp
//  Game Engine
//
//  Created by Indi Kernick on 4/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_input_keyboard_handler_hpp
#define engine_input_keyboard_handler_hpp

#include "keycode.hpp"
#include <memory>

namespace Input {
  class Manager;

  class KeyboardHandler {
  friend class Manager;
  public:
    using Ptr = std::shared_ptr<KeyboardHandler>;
  
    KeyboardHandler() = default;
    virtual ~KeyboardHandler() = default;
    
    virtual void onDown(Key::Type, Mod::Type) = 0;
    virtual void onUp(Key::Type, Mod::Type) = 0;
  protected:
    void focusOn();
    void focusOff();
  private:
    Manager *manager = nullptr;
  };
};

#include "manager.hpp"

#endif
