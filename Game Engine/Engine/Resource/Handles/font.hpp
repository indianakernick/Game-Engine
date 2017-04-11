//
//  font.hpp
//  Game Engine
//
//  Created by Indi Kernick on 11/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_resource_handles_font_hpp
#define engine_resource_handles_font_hpp

#include "../handle.hpp"
#include "../../Platform/Interface/font.hpp"
#include "../../Utils/combine.hpp"

namespace Res {
  struct NewFontInfo {
    uint32_t size;
    wchar_t firstChar = L' ';
    wchar_t numChars = L'~' - L' ';
    
    bool operator==(const NewFontInfo &) const;
    bool operator!=(const NewFontInfo &) const;
  };

  class Font final : public Handle {
  public:
    Font(Platform::Font::Ptr);
    ~Font() = default;
    
    Platform::Font::Ptr getFont() const;
  
  private:
    Platform::Font::Ptr font;
  };
}

template <>
struct std::hash<Res::NewFontInfo> {
  size_t operator()(const Res::NewFontInfo &) const;
};

#endif
