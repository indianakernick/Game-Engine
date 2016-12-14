//
//  global logger.hpp
//  Game Engine
//
//  Created by Indi Kernick on 14/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef global_logger_hpp
#define global_logger_hpp

#include "../Serial/xml.hpp"
#include <ctime>
#include <iostream>

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
    ANIMATION
  };
  
  enum Type {
    WARNING,
    ERROR,
    INFO,
    DEBUG
  };

  static bool init(std::string filePath = "log.xml",
                   XML::Node::Format format = {true, 2, 0});
  static void quit();
  static void write(Domain, Type, std::string message);
  
private:
  static std::unique_ptr<std::ofstream> file;
  static std::unique_ptr<XML::Node> document;
  static XML::Node::Format format;
  static bool initialized;
  
  static const std::string DOMAIN_STRINGS[];
  static const std::string TYPE_STRINGS[];
  
  static std::string getTime();
};

#endif
