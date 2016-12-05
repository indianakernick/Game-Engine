//
//  sdl.hpp
//  Game Engine
//
//  Created by Indi Kernick on 4/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef sdl_hpp
#define sdl_hpp

//#include <SDL2/SDL.h>

#ifdef _SDL_events_h

#include "../../Task Manager/task.hpp"
#include "../manager.hpp"

namespace Input {
  namespace Managers {
    class SDL : public Task, public Manager {
    public:
      SDL() = default;
      
      void enableRelativeMouse() override;
      void disableRelativeMouse() override;
      bool isRelativeMouseEnabled() override;
      
      void update(DeltaType) override;
    private:
      static Key::Type fromScancode(int);
      static MButton::Type fromIndex(uint8_t);
    };
  }
}

#endif

#endif
