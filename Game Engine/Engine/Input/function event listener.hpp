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
    FunctionEventListener() = default;
  
    void setMouseDownFunc(const std::function<bool (const MouseDown *)> &);
    void setMouseUpFunc(const std::function<bool (const MouseUp *)> &);
    void setMouseMoveFunc(const std::function<bool (const MouseMove *)> &);
    void setScrollFunc(const std::function<bool (const Scroll *)> &);
    void setKeyDownFunc(const std::function<bool (const KeyDown *)> &);
    void setKeyUpFunc(const std::function<bool (const KeyUp *)> &);
    void setWindowResizeFunc(const std::function<bool (const WindowResize *)> &);
    void setQuitFunc(const std::function<bool (const Quit *)> &);
    
  private:
    std::function<bool (const MouseDown *)> mouseDownFunc;
    std::function<bool (const MouseUp *)> mouseUpFunc;
    std::function<bool (const MouseMove *)> mouseMoveFunc;
    std::function<bool (const Scroll *)> scrollFunc;
    std::function<bool (const KeyDown *)> keyDownFunc;
    std::function<bool (const KeyUp *)> keyUpFunc;
    std::function<bool (const WindowResize *)> windowResizeFunc;
    std::function<bool (const Quit *)> quitFunc;
  
    bool onMouseDown(const MouseDown *) override;
    bool onMouseUp(const MouseUp *) override;
    bool onMouseMove(const MouseMove *) override;
    bool onScroll(const Scroll *) override;
    bool onKeyDown(const KeyDown *) override;
    bool onKeyUp(const KeyUp *) override;
    bool onWindowResize(const WindowResize *) override;
    bool onQuit(const Quit *) override;
  };
}

#endif
