//
//  font.hpp
//  Texture Atlas Generator
//
//  Created by Indi Kernick on 24/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef font_font_hpp
#define font_font_hpp

#include "../Image/types.hpp"
#include "freetype raii.hpp"
#include FT_FREETYPE_H

struct FontMetrics {
  SizePx lineHeight;
  PosPx minY;
  PosPx maxY;
};

using Font = FT_HANDLE(Face);

#endif
