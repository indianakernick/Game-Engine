//
//  logger.hpp
//  game engine
//
//  Created by Indi Kernick on 20/08/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef logger_hpp
#define logger_hpp

#include <fstream>
#include <string>
#include <stdexcept>
#include <ctime>//using ctime because it allows you to format time easily
#include <tuple>

class Logger {
private:
  template<size_t MAX, size_t I = 0>
  class Iter {
  public:
    template<typename ...ARGS>
    static void write(std::tuple<ARGS...> tuple, Logger *logger) {
      logger->file << std::get<I>(tuple);
      Iter<MAX, I + 1>::write(tuple, logger);
    }
  };

  template<size_t MAX>
  class Iter<MAX, MAX> {
  public:
    template<typename ...ARGS>
    static void write(std::tuple<ARGS...>, Logger *) {}
  };

public:
  Logger(std::string name);
  ~Logger();
  //is there a simpler way to iterate a variable argument list that doesn't
  //involve template metaprogramming
  template<typename ...ARGS>
  void write(ARGS ...args) {
    std::tuple<ARGS...> tuple(args...);
    if (!rawMode) {
      file << getTime() << timeSep;
    }
    Iter<sizeof...(args)>::write(tuple,this);
    if (rawMode) {
      file << std::flush;
    } else {
      file << std::endl;
    }
  }
  
  ///When raw is on the current time will not be prepended and
  ///the newline char will not be appended
  void raw(bool);
private:
  bool rawMode;
  std::ofstream file;
  
  static const char *timeSep;
  char timeStr[9];
  char* getTime();
};

#endif