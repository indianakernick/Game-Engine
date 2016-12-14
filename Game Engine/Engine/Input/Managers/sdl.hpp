//
//  sdl.hpp
//  Game Engine
//
//  Created by Indi Kernick on 4/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_input_managers_sdl_hpp
#define engine_input_managers_sdl_hpp

//#include <SDL2/SDL.h>

#ifdef _SDL_events_h

#include "../manager.hpp"

namespace Input {
  namespace Managers {
    class SDL : public Manager {
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
