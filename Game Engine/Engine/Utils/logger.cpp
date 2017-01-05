//
//  logger.cpp
//  Game Engine
//
//  Created by Indi Kernick on 14/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "logger.hpp"

FILE *Log::file = nullptr;
std::unique_ptr<tinyxml2::XMLPrinter> Log::printer;
bool Log::initialized = false;

const char *Log::DOMAIN_STRINGS[] {
  "Input",
  "UI",
  "Game Logic",
  "Game View",
  "Rendering",
  "Physics",
  "AI",
  "Audio",
  "Animation",
  "Game Events",
  "Application"
};

const char *Log::TYPE_STRINGS[] {
  "Warning",
  "Error",
  "Info",
  "Debug"
};

bool Log::init(const char *filePath) {
  if (!initialized) {
    std::cerr << "Log::init called with path " << filePath << '\n';
    file = fopen(filePath, "w");
    std::cerr << "file pointer " << file << '\n';
    if (file == nullptr) {
      std::cerr << "Failed to open file \"" << filePath << "\"\n";
      return false;
    }
    
    printer = std::make_unique<tinyxml2::XMLPrinter>(file);
    printer->PushHeader(false, true);
    printer->OpenElement("log");
    
    initialized = true;
  } else {
    std::cerr << "Log was initialized more than once\n";
  }
  return true;
}

void Log::quit() {
  if (initialized) {
    printer->CloseElement();
    printer.reset();
    fclose(file);
    file = nullptr;
    
    initialized = false;
  } else {
    std::cerr << "Log was destroyed before it was initialized (or it was destroyed twice)\n";
  }
}

void Log::write(Domain domain, Type type, const char *message) {
  printer->OpenElement("entry");
    printer->OpenElement("time");
      printer->PushText(getTime());
    printer->CloseElement();
    printer->OpenElement("domain");
      printer->PushText(DOMAIN_STRINGS[domain]);
    printer->CloseElement();
    printer->OpenElement("type");
      printer->PushText(TYPE_STRINGS[type]);
    printer->CloseElement();
    printer->OpenElement("message");
      printer->PushText(message);
    printer->CloseElement();
  printer->CloseElement();
  //making sure every entry is in the file before the program crashes
  fflush(file);
}

void Log::write(Domain domain, Type type, const std::string &message) {
  write(domain, type, message.c_str());
}

const char *Log::getTime() {
  time_t now;
  tm* timeinfo;
  static char out[9];

  time(&now);
  timeinfo = localtime(&now);
  strftime(out, 9, "%T", timeinfo);
  
  return out;
}
