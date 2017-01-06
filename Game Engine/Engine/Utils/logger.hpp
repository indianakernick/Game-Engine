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
#include <cassert>

class Log {
public:
  enum Domain {
    INPUT = 0,
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
    WARNING = 0,
    ERROR,
    INFO,
    ///Debug
    VERBOSE
  };
  
  enum TypeBit {
    BIT_MIN = 0,
    BIT_WARNING = 0b1,
    BIT_ERROR = 0b10,
    BIT_INFO = 0b100,
    BIT_VERBOSE = 0b1000,
    BIT_MAX = 0b1111
  };

  static bool init(const char *filePath = "log.xml");
  static void quit();
  static void write(Domain, Type, const char *);
  static void write(Domain, Type, const std::string &);
  ///Writes the log to stderr
  static void writeNow(Domain, Type, const char *);
  ///Writes the log to stderr
  static void writeNow(Domain, Type, const std::string &);
  
  ///Allow log types meaning they will be written to file
  ///or to stderr. All types are allowed by default
  static void allow(int);
  ///Disallow log types meaning they won't be written to file
  ///or to stderr. All types are allowed by default
  static void disallow(int);
  
private:
  static FILE *file;
  static std::unique_ptr<tinyxml2::XMLPrinter> printer;
  static bool initialized;
  //if their bits are here, they wont pass through
  static int filter;
  
  static const char *DOMAIN_STRINGS[];
  static const char *TYPE_STRINGS[];
  
  static const char *getTime();
};

#endif
