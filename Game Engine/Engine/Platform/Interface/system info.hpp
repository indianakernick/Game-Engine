//
//  system info.hpp
//  Game Engine
//
//  Created by Indi Kernick on 5/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_platform_interface_system_info_hpp
#define engine_platform_interface_system_info_hpp

#include <string>

namespace Platform {
  std::string getSaveDir(const std::string &, const std::string &);
  std::string getResDir();
  uint64_t getRAM();
}

#endif
