#include "path.hpp"
#import <Foundation/Foundation.h>

std::string Resource::path() {
  NSAutoreleasePool* pool = [[NSAutoreleasePool alloc] init];

  std::string rpath;
  NSBundle* bundle = [NSBundle mainBundle];

  if (bundle == nil) {
    #ifdef DEBUG
    NSLog(@"Failed to get resource path: there is no bundle");
    #endif
  } else {
    NSString* path = [bundle resourcePath];
    rpath = [path UTF8String] + std::string("/");
  }

  [pool drain];

  return rpath;
}
