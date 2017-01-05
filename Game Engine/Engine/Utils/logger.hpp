//
//  logger.hpp
//  Game Engine
//
//  Created by Indi Kernick on 14/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_utils_global_logger_hpp
#define engine_utils_global_logger_hpp

#include "../../Libraries/tinyxml2.hpp"
#include <ctime>
#include <iostream>
#include <cstdio>
#include <string>

class Log {
public:
  enum Domain {
    INPUT,
    UI,
    GAME_LOGIC,
    GAME_VIEW,
    RENDERING,
    PHYSICS,
    AI,
    AUDIO,
    ANIMATION,
    GAME_EVENTS,
    APPLICATION
  };
  
  enum Type {
    WARNING,
    ERROR,
    INFO,
    ///Debug
    VERBOSE
  };

  static bool init(const char *filePath = "log.xml");
  static void quit();
  static void write(Domain, Type, const char *);
  static void write(Domain, Type, const std::string &);
  
private:
  static FILE *file;
  static std::unique_ptr<tinyxml2::XMLPrinter> printer;
  static bool initialized;
  
  static const char *DOMAIN_STRINGS[];
  static const char *TYPE_STRINGS[];
  
  static const char *getTime();
};

#endif
