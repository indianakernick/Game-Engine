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

namespace Resource {
  class Loader {
  public:
    using Ptr = std::shared_ptr<Loader>;
  
    Loader() = default;
    virtual ~Loader() = default;
    
    ///What's your name
    virtual const std::string &getName() = 0;
    ///Can you load a file with this extension?
    virtual bool canLoad(const std::string &fileExt) = 0;
    ///Load a file and produce a handle
    virtual Handle::Ptr load(const ID &) = 0;
    
  protected:
    static std::string absPath(const ID &);
    static std::ifstream openFileStream(const ID &);
    static std::FILE *openFile(const ID &);
    ///If second is false, something went wrong
    static std::pair<Memory::Buffer, bool> readFile(const ID &);
  };
}

#endif
