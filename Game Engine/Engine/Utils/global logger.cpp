//
//  global logger.cpp
//  Game Engine
//
//  Created by Indi Kernick on 14/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "global logger.hpp"

std::unique_ptr<std::ofstream> Log::file;
std::unique_ptr<XML::Node> Log::document;
XML::Node::Format Log::format;
bool Log::initialized = false;

const std::string Log::DOMAIN_STRINGS[] {
  "Input",
  "UI",
  "Game Logic",
  "Game View",
  "Rendering",
  "Physics",
  "AI",
  "Audio",
  "Animation"
};

const std::string Log::TYPE_STRINGS[] {
  "Warning",
  "Error",
  "Info",
  "Debug"
};

bool Log::init(std::string filePath, XML::Node::Format format) {
  if (!initialized) {
    Log::format = format;
    
    file = std::make_unique<std::ofstream>(filePath);
    if (!file->is_open()) {
      std::cerr << "Failed to open log file\n";
      return false;
    }
    
    document = std::make_unique<XML::Node>("log");
    document->write(*file, format);
    
    initialized = true;
  } else {
    std::cerr << "Log was initialized more than once\n";
  }
  return true;
}

void Log::quit() {
  if (initialized) {
    document.reset();
    file.reset();
    
    initialized = false;
  } else {
    std::cerr << "Log was destroyed before it was initialized (or it was destroyed twice)\n";
  }
}

void Log::write(Domain domain, Type type, std::string message) {
  XML::NodePtr entry = XML::makeNode("entry");
  
  {
    XML::NodePtr time = XML::makeNode("time");
    time->setContent(getTime());
    entry->appendChild(time);
  }
  
  {
    XML::NodePtr domainNode = XML::makeNode("domain");
    domainNode->setContent(DOMAIN_STRINGS[domain]);
    entry->appendChild(domainNode);
  }
  
  {
    XML::NodePtr typeNode = XML::makeNode("type");
    typeNode->setContent(TYPE_STRINGS[type]);
    entry->appendChild(typeNode);
  }
  
  {
    XML::NodePtr messageNode = XML::makeNode("message");
    messageNode->setContent(message);
    entry->appendChild(messageNode);
  }
  
  document->appendChild(entry);
  file->seekp(0);
  document->write(*file, format);
}

std::string Log::getTime() {
  time_t now;
  tm* timeinfo;
  std::string out(8, ' ');

  time(&now);
  timeinfo = localtime(&now);
  strftime(const_cast<char *>(out.c_str()), 9, "%T", timeinfo);
  
  return out;
}
