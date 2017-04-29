//
//  font.hpp
//  Texture Atlas Generator
//
//  Created by Indi Kernick on 24/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef font_hpp
#define font_hpp

#include "../vector.hpp"
#include "freetype raii.hpp"
#include FT_FREETYPE_H
#include <string>

class Font {
public:
  struct Info {
    int pointSize;
    ivec2 dpi;
    wchar_t beginChar;
    wchar_t endChar;
  };
  
  struct Metrics {
    int lineHeight;
    int minY;
    int maxY;
  };
  
  Info info;
  Metrics metrics;
  FT_HANDLE(Face) face;
};

#endif
