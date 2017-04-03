//
//  strings.hpp
//  Game Engine
//
//  Created by Indi Kernick on 18/2/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_resource_handles_strings_hpp
#define engine_resource_handles_strings_hpp

#include "../handle.hpp"
#include <unordered_map>
#include <codecvt>

namespace Res {
  class Strings final : public Handle {
  friend class StringsLoader;
  public:
    using Ptr = std::shared_ptr<Strings>;
  
    Strings() = default;
    
    const std::wstring &get(const std::string &) const;
    std::string getBytes(const std::string &) const;
    const std::string &getLang() const;
  private:
    std::unordered_map<std::string, std::wstring> strings;
    std::string language;
    
    static const std::wstring EMPTY;
  };
}

#endif
