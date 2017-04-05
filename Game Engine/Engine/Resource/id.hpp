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
#include "../Utils/any.hpp"
#include "../Utils/combine.hpp"
#include <experimental/string_view>
#include "../Utils/logger.hpp"

namespace Res {
  class ID {
  friend std::hash<ID>;
  friend std::equal_to<ID>;
  public:
    ID();
    explicit ID(const std::string &path);
    explicit ID(std::string &&path);
    explicit ID(const char *path);
    ID(const std::string &path, Any data);
    ID(std::string &&path, Any data);
    ID(const char *path, Any data);
    
    ID(const ID &) = default;
    ID(ID &&) = default;
    
    ID &operator=(const ID &) = default;
    ID &operator=(ID &&) = default;
    
    ID &operator=(const std::string &newPath);
    ID &operator=(std::string &&newPath);
    ID &operator=(const char *newPath);
    
    explicit operator bool() const;
    
    const std::string &getPath() const;
    const char *getPathC() const;
    
    std::experimental::string_view getExt() const;
    std::experimental::string_view getEnclosingFolder() const;
    std::experimental::string_view getName() const;
    std::experimental::string_view getNameExt() const;
    const Any &getData() const;
    
    bool operator==(const ID &other) const;
    bool operator!=(const ID &other) const;
  private:
    std::string path;
    Any data;
    size_t hash;
    
    void init();
    void validatePath();
    void createHash();
  };
}

template <>
struct std::hash<Res::ID> {
  size_t operator()(const Res::ID &) const;
};

#endif
