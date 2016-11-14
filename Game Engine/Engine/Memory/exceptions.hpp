//
//  exceptions.hpp
//  game engine
//
//  Created by Indi Kernick on 10/11/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef exceptions_hpp
#define exceptions_hpp

#include <stdexcept>

namespace Memory {
  class OutOfMemory : public std::runtime_error {
  public:
    OutOfMemory(const std::string &what);
  };
  
  class OverRun : public std::runtime_error {
  public:
    OverRun(const std::string &what);
  };
  
  class UnderRun : public std::runtime_error {
  public:
    UnderRun(const std::string &what);
  };
  
  class Leak : public std::runtime_error {
  public:
    Leak(const std::string &what);
  };
  
  class BadPtr : public std::runtime_error {
  public:
    BadPtr(const std::string &what);
  };
}


#endif
