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
#include "path.hpp"

namespace Resource {
  class ID {
  friend std::hash<ID>;
  friend std::equal_to<ID>;
  public:
    ID();
    ID(std::nullptr_t);
    explicit ID(std::string path);
    explicit ID(const char *path);
    
    ID &operator=(const std::string &newPath);
    ID &operator=(const char *newPath);
    
    explicit operator bool() const;
    
    const std::string &getPath() const;
    const std::string &getExt() const;
    std::string getEnclosingFolder() const;
    
    const char *getPathC() const;
    const char *getExtC() const;
    
    bool operator==(const ID &other) const;
    bool operator!=(const ID &other) const;
  private:
    std::string path;
    std::string ext;
    size_t hash;
    
    void createExt();
    
    static std::hash<std::string> hasher;
  };
}

template <>
struct std::hash<Resource::ID> {
  size_t operator()(const Resource::ID &) const;
};

template <>
struct std::equal_to<Resource::ID> {
  bool operator()(const Resource::ID &, const Resource::ID &) const;
};

#endif
