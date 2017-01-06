//
//  manager.hpp
//  Game Engine
//
//  Created by Indi Kernick on 4/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_input_manager_hpp
#define engine_input_manager_hpp

#include <list>
#include "event.hpp"
#include "event listener.hpp"
#include <queue>
#include <functional>

namespace Input {
  using QuitListener = std::function<void ()>;

  class Manager {
  public:
    using Ptr = std::shared_ptr<Manager>;
  
    Manager(Geometry::Size);
    virtual ~Manager() = default;
    
    void addListener(EventListener::Ptr);
    void remListener(EventListener::Ptr);
    
    void addQuitListener(QuitListener);
    void remQuitListener(QuitListener);
    
    void update();
  protected:
    bool keyState[Key::NUM_OF_KEYS] = {0};
    bool mouseState[MButton::NUM_OF_BUTTONS] = {0};
    Geometry::Point mousePos;
    Geometry::Size windowSize;
    
    void sendEvent(Event::Ptr);
    void quitEvent(Quit::Ptr);
  
    virtual void sendEvents() = 0;
  private:
    std::list<EventListener::Ptr> listeners;
    std::list<QuitListener> quitListeners;
    std::queue<Event::Ptr> eventQueue;
  };
};

#endif
