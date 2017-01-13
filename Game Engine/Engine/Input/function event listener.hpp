//
//  function event listener.hpp
//  Game Engine
//
//  Created by Indi Kernick on 12/1/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_input_function_event_listener_hpp
#define engine_input_function_event_listener_hpp

#include "event listener.hpp"
#include <functional>

namespace Input {
  class FunctionEventListener : public EventListener {
  public:
    explicit FunctionEventListener(bool cast = true);
  
    void setEventFunc(const std::function<void (Event::Ptr)> &);
    void setMouseDownFunc(const std::function<void (MouseDown::Ptr)> &);
    void setMouseUpFunc(const std::function<void (MouseUp::Ptr)> &);
    void setMouseMoveFunc(const std::function<void (MouseMove::Ptr)> &);
    void setScrollFunc(const std::function<void (Scroll::Ptr)> &);
    void setKeyDownFunc(const std::function<void (KeyDown::Ptr)> &);
    void setKeyUpFunc(const std::function<void (KeyUp::Ptr)> &);
    void setWindowResizeFunc(const std::function<void (WindowResize::Ptr)> &);
    void setQuitFunc(const std::function<void (Quit::Ptr)> &);
    
  private:
    std::function<void (Event::Ptr)> eventFunc;
    std::function<void (MouseDown::Ptr)> mouseDownFunc;
    std::function<void (MouseUp::Ptr)> mouseUpFunc;
    std::function<void (MouseMove::Ptr)> mouseMoveFunc;
    std::function<void (Scroll::Ptr)> scrollFunc;
    std::function<void (KeyDown::Ptr)> keyDownFunc;
    std::function<void (KeyUp::Ptr)> keyUpFunc;
    std::function<void (WindowResize::Ptr)> windowResizeFunc;
    std::function<void (Quit::Ptr)> quitFunc;
  
    bool onEvent(Event::Ptr) override;
    bool onMouseDown(MouseDown::Ptr) override;
    bool onMouseUp(MouseUp::Ptr) override;
    bool onMouseMove(MouseMove::Ptr) override;
    bool onScroll(Scroll::Ptr) override;
    bool onKeyDown(KeyDown::Ptr) override;
    bool onKeyUp(KeyUp::Ptr) override;
    bool onWindowResize(WindowResize::Ptr) override;
    bool onQuit(Quit::Ptr) override;
  };
}

#endif
