//
//  strings.hpp
//  Game Engine
//
//  Created by Indi Kernick on 18/2/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_resource_loaders_strings_hpp
#define engine_resource_loaders_strings_hpp

#include "../loader.hpp"
#include "../Handles/strings.hpp"
#include <codecvt>
#include "line col.hpp"

namespace Res {
  class StringsParseError : public std::runtime_error {
  public:
    StringsParseError(std::string what);
  };

  class StringsLoader : public Loader {
  public:
    const std::string &getName() const override;
    bool canLoad(const std::string &ext) const override;
    Handle::Ptr load(const ID &id) const override;
  
  private:
    enum State {
      NO_CHANGE,
    
      WHITE_SPACE,
      COMMENT,
      KEY_STR,
      AFTER_KEY_STR,
      BEFORE_VAL_STR,
      VAL_STR,
      AFTER_VAL_STR
    };
    
    static void changeState(State &state, State newState);
    static void handleState(State &, char, std::string &, std::string &, Strings::Ptr);
    
    static State whiteSpace(char);
    static State comment(char);
    static State keyStr(char, std::string &key);
    static State afterKeyStr(char);
    static State beforeValStr(char);
    static State valStr(char, std::string &val);
    static State afterValStr(char, std::string &, std::string &, Strings::Ptr);
  };
}

#endif
