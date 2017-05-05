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
  struct Size {
    int points;
    ivec2 dpi;
  };
  
  struct Metrics {
    int lineHeight;
    int minY;
    int maxY;
  };
  
  Size size;
  Metrics metrics;
  FT_HANDLE(Face) face;
};

#endif
