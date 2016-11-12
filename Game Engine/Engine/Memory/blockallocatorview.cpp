//
//  blockallocatorview.cpp
//  game engine
//
//  Created by Indi Kernick on 7/10/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "blockallocatorview.hpp"

#ifdef DEBUG
std::map<void *, Buffer::AllocInfo> Buffer::allocInfo;
std::map<void *, Buffer::FreeInfo> Buffer::freeInfo;

void Buffer::checkSafety() {
  for (auto i = allocInfo.begin(); i != allocInfo.end(); ++i) {
    std::cerr << "Memory leaked in file " << i->second.file << " on line " << i->second.line << '\n';
  }
}
#endif