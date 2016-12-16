//
//  sdl.hpp
//  Game Engine
//
//  Created by Indi Kernick on 16/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_application_libraries_sdl_hpp
#define engine_application_libraries_sdl_hpp

#include "library.hpp"
#include "../../Math/byteconstants.hpp"

//#include <SDL2/SDL.h>

#ifdef _SDL_H

namespace Libraries {
  class SDL : public Library {
  public:
    void init() override;
    void quit() override;
    
    std::string getSaveDir(std::string companyName, std::string appName) override;
    uint64_t getSystemRAM() override;
  };
}

#endif

#endif
