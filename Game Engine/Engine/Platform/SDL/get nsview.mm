//
//  get nsview.mm
//  Game Engine
//
//  Created by Indi Kernick on 17/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "get nsview.hpp"

#import <Cocoa/Cocoa.h>

uintptr_t Platform::getNSView(void *windowPtr) {
  NSWindow *window = reinterpret_cast<NSWindow *>(windowPtr);
  NSView *view = [window contentView];
  return reinterpret_cast<uintptr_t>(view);
}
