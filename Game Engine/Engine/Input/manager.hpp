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
#include "../Task Manager/task.hpp"
#include "event.hpp"
#include "event listener.hpp"
#include <queue>

namespace Input {
  class Manager : public Task {
  public:
    using Ptr = std::shared_ptr<Manager>;
  
    Manager() = default;
    virtual ~Manager() = default;
    
    void addListener(EventListener::Ptr);
    void remListener(EventListener::Ptr);
    
    virtual void enableRelativeMouse() = 0;
    virtual void disableRelativeMouse() = 0;
    virtual bool isRelativeMouseEnabled() = 0;
    
    virtual void enableMouseCapture() = 0;
    virtual void disableMouseCapture() = 0;
    
    void update(DeltaType) override;
    
    virtual void update() = 0;
  protected:
    bool keyState[Key::NUM_OF_KEYS] = {0};
    bool mouseState[MButton::NUM_OF_BUTTONS] = {0};
    Geometry::Point mousePos;
    Geometry::Size windowSize;
    
    void sendEvent(Event::Ptr);
  
  private:
    std::list<EventListener::Ptr> listeners;
    std::queue<Event::Ptr> eventQueue;
  };
};

#endif
