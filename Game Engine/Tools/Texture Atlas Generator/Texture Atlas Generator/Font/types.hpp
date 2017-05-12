//
//  types.hpp
//  Texture Atlas Generator
//
//  Created by Indi Kernick on 6/5/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef font_types_hpp
#define font_types_hpp

#include "../Utils/types.hpp"

using CodePoint = char;
using SizePt = SizePx;
using DPI = SizePx2;

struct CodePointRange {
  CodePoint begin;
  CodePoint end;
};

#endif
