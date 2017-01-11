//
//  strings.hpp
//  Game Engine
//
//  Created by Indi Kernick on 14/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_utils_strings_hpp
#define engine_utils_strings_hpp

#include "../Application/global resource cache.hpp"
#include "../Resource/Handles/xml.hpp"
#include <unordered_map>
#include <string>
#include "logger.hpp"
#include <codecvt>
#include <memory>

class Strings {
public:
  using Ptr = std::shared_ptr<Strings>;

  Strings(const std::string &language);
  
  void load();
  std::wstring get(const std::string &) const;
  
private:
  std::unordered_map<std::string, std::wstring> strings;
  std::string language;
  
  static std::wstring_convert<std::codecvt_utf8<wchar_t>> strConverter;
};

#endif
