//
//  path.mm
//  Game Engine
//
//  Created by Indi Kernick on 11/11/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "path.hpp"

#import <Foundation/Foundation.h>

const std::string &Res::path() {
  static std::string path;
  if (path.empty()) {
    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];

    NSBundle *bundle = [NSBundle mainBundle];

    if (bundle == nil) {
      LOG_ERROR(RESOURCES, "Failed to get resource path: bundle is missing");
    } else {
      NSString *resPath = [bundle resourcePath];
      if (resPath == nil) {
        LOG_ERROR(RESOURCES, "Failed to get resource path: bundle doesn't have a Resources folder");
      } else {
        path = [resPath cStringUsingEncoding:(NSASCIIStringEncoding)] + std::string("/");
      }
    }

    [pool drain];
  }
  return path;
}
