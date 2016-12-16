//
//  library.hpp
//  Game Engine
//
//  Created by Indi Kernick on 16/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_application_library_hpp
#define engine_application_library_hpp

#include <string>
#include <memory>
#include "window.hpp"

class Library {
public:
  using Ptr = std::shared_ptr<Library>;

  Library() = default;
  virtual ~Library() = default;
  
  virtual void init() = 0;
  virtual void quit() = 0;
  
  virtual Window::Ptr makeWindow() = 0;
  
  virtual std::string getSaveDir(std::string companyName, std::string appName) = 0;
  virtual uint64_t getSystemRAM() = 0;
};

#endif
