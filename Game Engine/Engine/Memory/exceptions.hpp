//
//  exceptions.hpp
//  Game Engine
//
//  Created by Indi Kernick on 10/11/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_memory_exceptions_hpp
#define engine_memory_exceptions_hpp

#include <stdexcept>
#include <string>

namespace Memory {
  class OutOfMemory final : public std::runtime_error {
  public:
    OutOfMemory(const std::string &what);
  };
  
  class OverRun final : public std::runtime_error {
  public:
    OverRun(const std::string &what);
  };
  
  class UnderRun final : public std::runtime_error {
  public:
    UnderRun(const std::string &what);
  };
  
  class Leak final : public std::runtime_error {
  public:
    Leak(const std::string &what);
  };
  
  class BadPtr final : public std::runtime_error {
  public:
    BadPtr(const std::string &what);
  };
}


#endif
