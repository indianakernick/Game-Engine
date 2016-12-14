//
//  strings.cpp
//  Game Engine
//
//  Created by Indi Kernick on 14/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "strings.hpp"

Strings::Strings(Resource::Cache *cache, std::string language) {
  assert(cache);
  //xml loader can't load from memory
}

std::wstring Strings::get(const std::string &id) const {
  auto iter = strings.find(id);
  if (iter == strings.end()) {
    return L"";
  } else {
    return iter->second;
  }
}

std::wstring Strings::get(std::string &&id) const {
  auto iter = strings.find(std::move(id));
  if (iter == strings.end()) {
    return L"";
  } else {
    return iter->second;
  }
}
