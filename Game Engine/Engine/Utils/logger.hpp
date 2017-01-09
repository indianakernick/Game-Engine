//
//  logger.hpp
//  Game Engine
//
//  Created by Indi Kernick on 14/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_utils_logger_hpp
#define engine_utils_logger_hpp

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
    APPLICATION,
    SCENE_GRAPH
  };
  
  enum Severity {
    ///Debug
    VERBOSE = 0,
    INFO,
    WARNING,
    ERROR,
  };
  
  enum SeverityBit {
    BIT_MIN = 0,
    
    BIT_WARNING = 0b1,
    BIT_ERROR = 0b10,
    BIT_INFO = 0b100,
    BIT_VERBOSE = 0b1000,
    BIT_ALL = 0b1111,
    
    BIT_MAX = BIT_ALL
  };

  static bool init(const char *filePath = "log.xml");
  static void quit();
  static void write(Domain, Severity, const char *, const char *, int, const char *, ...);
  
  ///Allow log severities meaning they will be written to file
  ///or to stderr. All severities are allowed by default
  static void allow(SeverityBit);
  ///Disallow log severities meaning they won't be written to file
  ///or to stderr. All severities are allowed by default
  static void disallow(SeverityBit);
  ///Checks whether a severity level is allowed and will be processed normally
  static bool allowed(SeverityBit);
  
private:
  static FILE *file;
  static std::unique_ptr<tinyxml2::XMLPrinter> printer;
  static bool initialized;
  //if their bits are here, they wont pass through
  static int filter;
  
  static const char *DOMAIN_STRINGS[];
  static const char *SEVERITY_STRINGS[];
};

#define LOG(domain, severity, ...) Log::write(Log::domain, Log::severity, __FILE__, __PRETTY_FUNCTION__, __LINE__, __VA_ARGS__)
#define LOG_DEBUG(domain, ...) LOG(domain, VERBOSE, __VA_ARGS__)
#define LOG_INFO(domain, ...) LOG(domain, INFO, __VA_ARGS__)
#define LOG_WARNING(domain, ...) LOG(domain, WARNING, __VA_ARGS__)
#define LOG_ERROR(domain, ...) LOG(domain, ERROR, __VA_ARGS__)

#endif
