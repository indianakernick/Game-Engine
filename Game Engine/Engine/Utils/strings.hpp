//
//  strings.hpp
//  Game Engine
//
//  Created by Indi Kernick on 14/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef strings_hpp
#define strings_hpp

#include "../Resource/cache.hpp"
#include <unordered_map>

class Strings {
public:
  Strings(Resource::Cache *cache, std::string language);
  
  std::wstring get(const std::string &id) const;
  std::wstring get(std::string &&id) const;
  
private:
  std::unordered_map<std::string, std::wstring> strings;
};

#endif
