//
//  logger.hpp
//  Game Engine
//
//  Created by Indi Kernick on 14/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_utils_logger_hpp
#define engine_utils_logger_hpp

#include <iostream>
#include <cstdio>
#include <cassert>

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
    APPLICATION,
    SCENE_GRAPH,
    RESOURCES
  };
  
  enum Severity {
    ///Debug
    VERBOSE,
    INFO,
    WARNING,
    ERROR,
  };
  
  Log() = delete;
  ~Log() = delete;

  static bool init(const char *filePath);
  static void quit();
  static void write(Domain, Severity, const char *, const char *, int, const char *, ...);
  
private:
  static std::FILE *file;
  static bool initialized;
  static ptrdiff_t filePathOffset;
  
  static const char *DOMAIN_STRINGS[];
  static const char *SEVERITY_STRINGS[];
  
  struct Entry {
    Domain domain;
    Severity severity;
    const char *file;
    const char *function;
    int line;
    const char *message;
  };
  
  static const size_t MAX_PRE_INIT_ENTRIES = 8;
  static Entry preInitEntries[MAX_PRE_INIT_ENTRIES];
  static size_t numPreInitEntries;
  
  static void writeToFile(Domain, Severity, const char *, const char *, int, const char *);
  static void preInitWrite(const Entry &);
  static void flushPreInitEntries();
};

#define LOG(domain, severity, ...) Log::write(Log::Domain::domain, Log::Severity::severity, __FILE__, __PRETTY_FUNCTION__, __LINE__, __VA_ARGS__)

#ifdef LOG_DEBUG_ASSERT
#define LOG_DEBUG(domain, ...) printf(__VA_ARGS__);putchar('\n');assert(false)
#elif defined(LOG_DEBUG_CHECK_ARGS)
//many compilers check that the format string matchs the arguments
//but they can only do this if they can see the call
#define LOG_DEBUG(domain, ...) printf(__VA_ARGS__);putchar('\n')
#elif defined(LOG_DEBUG_NONE)
#define LOG_DEBUG(domain, ...)
#else
#define LOG_DEBUG(domain, ...) LOG(domain, VERBOSE, __VA_ARGS__)
#endif

#ifdef LOG_INFO_ASSERT
#define LOG_INFO(domain, ...) printf(__VA_ARGS__);putchar('\n');assert(false)
#elif defined(LOG_INFO_CHECK_ARGS)
#define LOG_INFO(domain, ...) printf(__VA_ARGS__);putchar('\n')
#elif defined(LOG_INFO_NONE)
#define LOG_INFO(domain, ...)
#else
#define LOG_INFO(domain, ...) LOG(domain, INFO, __VA_ARGS__)
#endif

#ifdef LOG_WARNING_ASSERT
#define LOG_WARNING(domain, ...) printf(__VA_ARGS__);putchar('\n');assert(false)
#elif defined(LOG_WARNING_CHECK_ARGS)
#define LOG_WARNING(domain, ...) printf(__VA_ARGS__);putchar('\n')
#elif defined(LOG_WARNING_NONE)
#define LOG_WARNING(domain, ...)
#else
#define LOG_WARNING(domain, ...) LOG(domain, WARNING, __VA_ARGS__)
#endif

#ifdef LOG_ERROR_ASSERT
#define LOG_ERROR(domain, ...) printf(__VA_ARGS__);putchar('\n');assert(false)
#elif defined(LOG_ERROR_CHECK_ARGS)
#define LOG_ERROR(domain, ...) printf(__VA_ARGS__);putchar('\n')
#elif defined(LOG_ERROR_NONE)
#define LOG_ERROR(domain, ...)
#else
#define LOG_ERROR(domain, ...) LOG(domain, ERROR, __VA_ARGS__)
#endif

#endif
