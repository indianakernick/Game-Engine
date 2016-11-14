//
//  exceptions.cpp
//  game engine
//
//  Created by Indi Kernick on 10/11/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "exceptions.hpp"

Buffer::OutOfMemory::OutOfMemory(const std::string &what)
  : std::runtime_error(what) {}

Buffer::OverRun::OverRun(const std::string &what)
  : std::runtime_error(what) {}

Buffer::UnderRun::UnderRun(const std::string &what)
  : std::runtime_error(what) {}

Buffer::Leak::Leak(const std::string &what)
  : std::runtime_error(what) {}

Buffer::BadPtr::BadPtr(const std::string &what)
  : std::runtime_error(what) {}
