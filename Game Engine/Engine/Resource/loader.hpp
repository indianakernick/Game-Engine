//
//  loader.hpp
//  Game Engine
//
//  Created by Indi Kernick on 10/1/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_resource_loader_hpp
#define engine_resource_loader_hpp

#include <string>
#include <experimental/string_view>
#include "../Memory/buffer.hpp"
#include "handle.hpp"
#include "id.hpp"
#include <fstream>
#include "path.hpp"
#include <vector>

namespace Res {
  class FileError final : public std::runtime_error {
  public:
    FileError(const char *what);
  };

  class Loader {
  public:
    using Ptr = std::shared_ptr<Loader>;
  
    Loader() = default;
    virtual ~Loader() = default;
    
    ///What's your name?
    virtual const std::string &getName() const = 0;
    ///Can you load a file with this extension?
    virtual bool canLoad(std::experimental::string_view) const = 0;
    ///Load a file and produce a handle
    virtual Handle::Ptr load(const ID &) const = 0;
    
  protected:
    using FileHandle = std::unique_ptr<std::FILE, int(*)(std::FILE *)>;
  
    static std::string absPath(const ID &);
    static std::ifstream openFileStream(const ID &);
    static FileHandle openFile(const ID &);
    static Memory::Buffer readFile(const ID &);
    
    template <size_t SIZE>
    static bool hasExt(const char *(&exts)[SIZE], std::experimental::string_view ext) {
      //the extensions in exts are assumed to be null terminated
      return std::any_of(exts, exts + SIZE, [ext] (const char *thisExt) {
        return std::strncmp(thisExt, ext.data(), ext.size()) == 0;
      });
    }
  };
}

#endif
