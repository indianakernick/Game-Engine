//
//  freetype log error.cpp
//  Game Engine
//
//  Created by Indi Kernick on 30/3/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "freetype log error.hpp"

#ifndef NDEBUG

const char *Platform::getFTErrorString(FT_Error error) {
  switch (error) {
    #define FT_NOERRORDEF_(e, v, s)
    #define FT_ERRORDEF_(e, v, s) case v: return s;
    #include FT_ERROR_DEFINITIONS_H
    #undef FT_NOERRORDEF_
    #undef FT_ERRORDEF_
    
    default:
      return "(Unknown)";
  }
}

#endif
