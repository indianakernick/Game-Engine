//
//  logger.cpp
//  Game Engine
//
//  Created by Indi Kernick on 20/08/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "logger.hpp"

const char *Logger::timeSep = "   |   ";

Logger::Logger(std::string name) {
  file.open(name);
  if (file.is_open()) {
    file << getTime() << timeSep << "INITIALISED LOGGER" << std::endl;
    file.setf(file.boolalpha);
  } else {
    throw std::runtime_error("Failed to open file \"" + name + "\"");
  }
}

Logger::~Logger() {
  if (file.is_open()) {
    file << getTime() << timeSep << "DESTROYED LOGGER" << std::endl;
    file.close();
  }
}

/*void Logger::write(std::string message) {
  if (rawMode) {
    file << message << std::flush;
  } else {
    file << getTime() << timeSep << message << std::endl;
  }
}*/

void Logger::raw(bool newRaw) {
  if (newRaw != rawMode) {
    rawMode = newRaw;
    file << getTime() << timeSep;
    if (newRaw) {
      file << "STARTING RAW MODE\n";
    } else {
      file << "ENDING RAW MODE\n";
    }
  }
}

char* Logger::getTime() {
  time_t now;
  tm* timeinfo;

  time(&now);
  timeinfo = localtime(&now);
  strftime(timeStr,9,"%T",timeinfo);
  
  return timeStr;
}
