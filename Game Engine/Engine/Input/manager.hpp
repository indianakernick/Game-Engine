//
//  manager.hpp
//  Game Engine
//
//  Created by Indi Kernick on 4/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_input_manager_hpp
#define engine_input_manager_hpp

#include "handlers/mouse.hpp"
#include "handlers/keyboard.hpp"
#include <list>
#include <functional>
#include "../Task Manager/task.hpp"

namespace Input {
  using QuitHandler = std::function<void ()>;

  class Manager : public Task {
  friend class Handlers::Mouse;
  friend class Handlers::Keyboard;
  public:
    using Ptr = std::shared_ptr<Manager>;
  
    Manager() = default;
    virtual ~Manager() = default;
    
    void addQuitHandler(QuitHandler);
    void remQuitHandler(QuitHandler);
    
    void addMouseHandler(Handlers::Mouse::Ptr);
    void addKeyboardHandler(Handlers::Keyboard::Ptr);
    
    void remMouseHandler(Handlers::Mouse::Ptr);
    void remKeyboardHandler(Handlers::Keyboard::Ptr);
    
    virtual void enableRelativeMouse() = 0;
    virtual void disableRelativeMouse() = 0;
    virtual bool isRelativeMouseEnabled() = 0;
    
    //for polling events and calling handler functions
    virtual void update(DeltaType) = 0;
  protected:
    bool keyState[Key::NUM_OF_KEYS] = {0};
    bool mouseState[MButton::NUM_OF_BUTTONS] = {0};
    Geometry::Point mousePos;
    
    void quit();
    
    void mouseMovedAbs(Geometry::Point newPos);
    void mouseMovedRel(Geometry::Point delta);
    
    void mouseScroll(Geometry::Point delta);
    
    void mouseDown(MButton::Type);
    void mouseUp(MButton::Type);
    
    void keyDown(Key::Type);
    void keyUp(Key::Type);
  
  private:
    std::list<std::function<void ()>> quitHandlers;
    std::list<Handlers::Mouse::Ptr> mouseHandlers;
    std::list<Handlers::Keyboard::Ptr> keyboardHandlers;
    Handlers::Mouse *mouseCapture = nullptr;
    Handlers::Keyboard *keyboardFocus = nullptr;
    
    /*
    too many parameters
    
    template <typename HANDLER, typename METHOD, typename ...ARGS>
    void dispatch(HANDLER *single, std::list<typename HANDLER::Ptr> handlers, METHOD method, ARGS ...args) {
      auto func = std::mem_fn(method);
      if (single) {
        func(single, std::forward<ARGS>(args)...);
      } else {
        for (auto i = handlers.begin(); i != handlers.end(); ++i) {
          if (func((*i).get(), std::forward<ARGS>(args)...)) {
            return;
          }
        }
      }
    }*/
    
    template <typename METHOD, typename ...ARGS>
    void mouseEvent(METHOD method, ARGS ...args) {
      auto func = std::mem_fn(method);
      if (mouseCapture) {
        func(mouseCapture, std::forward<ARGS>(args)...);
      } else {
        for (auto i = mouseHandlers.begin(); i != mouseHandlers.end(); ++i) {
          if (func((*i).get(), std::forward<ARGS>(args)...)) {
            return;
          }
        }
        //not handled
      }
    }
    
    template <typename METHOD, typename ...ARGS>
    void keyEvent(METHOD method, ARGS ...args) {
      auto func = std::mem_fn(method);
      if (keyboardFocus) {
        func(keyboardFocus, std::forward<ARGS>(args)...);
      } else {
        for (auto i = keyboardHandlers.begin(); i != keyboardHandlers.end(); ++i) {
          if (func((*i).get(), std::forward<ARGS>(args)...)) {
            return;
          }
        }
        //not handled
      }
    }
    
    void setMouseCapture(Handlers::Mouse *);
    void setKeyboardFocus(Handlers::Keyboard *);
  };
};

#endif
