//
//  blockallocatorview.cpp
//  game engine
//
//  Created by Indi Kernick on 7/10/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "blockallocatorview.hpp"

#ifdef DEBUG
std::map<void *, Memory::AllocInfo> Memory::allocInfo;
std::map<void *, Memory::FreeInfo> Memory::freeInfo;

void Memory::checkSafety() {
  for (auto i = allocInfo.begin(); i != allocInfo.end(); ++i) {
    std::cerr << "Memory leaked in file " << i->second.file << " on line " << i->second.line << '\n';
  }
}
#endif
