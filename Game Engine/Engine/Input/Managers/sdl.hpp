//
//  sdl.hpp
//  Game Engine
//
//  Created by Indi Kernick on 4/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_input_managers_sdl_hpp
#define engine_input_managers_sdl_hpp

#ifdef USE_SDL

#include <SDL2/SDL_events.h>
#include "../manager.hpp"
#include "../../Utils/logger.hpp"

namespace Input {
  namespace Managers {
    class SDL : public Manager {
    public:
      SDL(Geometry::Size);
    private:
      static Key::Type fromScancode(int);
      static MButton::Type fromIndex(uint8_t);
      
      void sendEvents() override;
      void sendMouseDown(const SDL_Event &);
      void sendMouseUp(const SDL_Event &);
      void sendMouseMove(const SDL_Event &);
      void sendScroll(const SDL_Event &);
      void sendKeyDown(const SDL_Event &);
      void sendKeyUp(const SDL_Event &);
      void sendWindow(const SDL_Event &);
      void sendQuit(const SDL_Event &);
    };
  }
}

#endif

#endif
