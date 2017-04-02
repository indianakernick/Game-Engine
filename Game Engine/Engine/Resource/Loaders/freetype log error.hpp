//
//  freetype log error.hpp
//  Game Engine
//
//  Created by Indi Kernick on 30/3/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_resource_loaders_freetype_log_error_hpp
#define engine_resource_loaders_freetype_log_error_hpp

#include "../../Utils/logger.hpp"
#include <ft2build.h>
#include FT_TYPES_H

const char *getFTErrorString(FT_Error);

#define LOG_FT_ERROR(error) \
  if ((error) != 0) { \
    LOG_ERROR(RESOURCES, "Freetype error: %s", getFTErrorString(error)); \
  }

#endif
