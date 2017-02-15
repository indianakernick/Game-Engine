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
#include "../Memory/buffer.hpp"
#include "handle.hpp"
#include "id.hpp"
#include <fstream>
#include "path.hpp"
#include <vector>

namespace Res {
  class FileError : public std::runtime_error {
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
    virtual bool canLoad(const std::string &) const = 0;
    ///Load a file and produce a handle
    virtual Handle::Ptr load(const ID &) const = 0;
    
  protected:
    static std::string absPath(const ID &);
    static std::ifstream openFileStream(const ID &);
    static std::FILE *openFile(const ID &);
    static Memory::Buffer readFile(const ID &);
    static bool hasExt(const std::vector<std::string> &exts,
                       const std::string &ext);
    template <size_t SIZE>
    static bool hasExt(const std::string (&exts)[SIZE],
                       const std::string &ext) {
      return std::any_of(exts, exts + SIZE, [&ext](const std::string &thisExt) {
        return ext == thisExt;
      });
    }
    template <size_t SIZE>
    static bool hasExt(const std::array<const std::string, SIZE> &exts,
                       const std::string &ext) {
      return std::any_of(exts.cbegin(), exts.cend(), [&ext](const std::string &thisExt) {
        return ext == thisExt;
      });
    }
  };
}

#endif
