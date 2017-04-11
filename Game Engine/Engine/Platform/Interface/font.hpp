//
//  font.hpp
//  Game Engine
//
//  Created by Indi Kernick on 10/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_platform_interface_font_hpp
#define engine_platform_interface_font_hpp

#include <string>
#include <memory>

namespace Platform {
  class Font {
  public:
    using Ptr = std::shared_ptr<Font>;
  
    Font() = default;
    virtual ~Font() = default;
    
    virtual size_t getByteSize() const = 0;
  };
}

#endif
