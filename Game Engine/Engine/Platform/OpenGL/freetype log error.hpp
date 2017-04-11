//
//  freetype log error.hpp
//  Game Engine
//
//  Created by Indi Kernick on 30/3/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_platform_opengl_freetype_log_error_hpp
#define engine_platform_opengl_freetype_log_error_hpp

#ifdef USE_OPENGL

#ifdef NDEBUG

#define LOG_FT_ERROR(error) (error)

#else

#include "../../Utils/logger.hpp"
#include <ft2build.h>
#include FT_TYPES_H

namespace Platform {
  const char *getFTErrorString(FT_Error);
}

#define LOG_FT_ERROR(error) \
  if ((error) != 0) { \
    LOG_ERROR(RESOURCES, "Freetype error: %s", Platform::getFTErrorString(error)); \
  }

#endif //NDEBUG

#endif //USE_OPENGL

#endif
