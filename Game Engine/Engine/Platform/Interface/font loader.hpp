//
//  font loader.hpp
//  Game Engine
//
//  Created by Indi Kernick on 11/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_platform_interface_font_loader_hpp
#define engine_platform_interface_font_loader_hpp

#include "font.hpp"
#include "../../Memory/buffer.hpp"
#include <stdexcept>

namespace Platform {
  class FontLoadError final : public std::runtime_error {
  public:
    FontLoadError(const char *);
  };

  Font::Ptr loadFont(Memory::Buffer, uint32_t, wchar_t, wchar_t);
}

#endif
