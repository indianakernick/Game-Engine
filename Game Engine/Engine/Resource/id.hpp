//
//  id.hpp
//  Game Engine
//
//  Created by Indi Kernick on 26/11/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_resource_id_hpp
#define engine_resource_id_hpp

#include <string>

namespace Resource {
  class ID {
  public:
    explicit ID(std::string path);
    
    const std::string &getPath() const;
    
    //for compatability with std::map
    bool operator<(const ID &other) const;
    bool operator==(const ID &other) const;
    bool operator!=(const ID &other) const;
  private:
    std::string path;
  };
}

#endif
