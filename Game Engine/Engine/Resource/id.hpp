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
#include <functional>

namespace Resource {
  class ID {
  public:
    ID();
    ID(std::nullptr_t);
    explicit ID(std::string path);
    explicit ID(const char *path);
    
    ID &operator=(const std::string &newPath);
    ID &operator=(const char *newPath);
    
    const std::string &getPath() const;
    ///Was default constructed
    bool isNull() const;
    
    //for compatability with std::map
    bool operator<(const ID &other) const;
    bool operator==(const ID &other) const;
    bool operator!=(const ID &other) const;
  private:
    std::string path;
    size_t hash;
    
    static std::hash<std::string> hasher;
  };
}

#endif
