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
int Log::filter = 0;
Log::Entry Log::preInitEntries[MAX_PRE_INIT_ENTRIES];
size_t Log::numPreInitEntries = 0;

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
  "Application",
  "Scene Graph"
};

const char *Log::SEVERITY_STRINGS[] {
  "Debug",
  "Info",
  "Warning",
  "Error"
};

bool Log::init(const char *filePath) {
  if (!initialized) {
    file = fopen(filePath, "w");
    if (file == nullptr) {
      std::cerr << "Failed to open file \"" << filePath << "\"\n";
      return false;
    }
    
    printer = std::make_unique<tinyxml2::XMLPrinter>(file);
    printer->PushHeader(false, true);
    printer->OpenElement("log");
    
    initialized = true;
    
    flushPreInitEntries();
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

void Log::write(Domain domain, Severity severity, const char *fileName,
                const char *function, int line, const char *format, ...) {
  if (filter & severity) {
    return;
  }
  
  va_list list;
  va_start(list, format);
  static char message[256];
  vsnprintf(message, 256, format, list);
  
  if (initialized) {
    writeToFile(domain, severity, fileName, function, line, message);
  } else {
    preInitWrite({domain, severity, fileName, function, line, message});
  }
}

void Log::allow(SeverityBit severity) {
  assert(BIT_MIN < severity && severity <= BIT_MAX);
  filter &= ~severity;
}

void Log::disallow(SeverityBit severity) {
  assert(BIT_MIN < severity && severity <= BIT_MAX);
  filter |= severity;
}

bool Log::allowed(SeverityBit severity) {
  assert(BIT_MIN < severity && severity <= BIT_MAX);
  return !(filter & severity);
}

void Log::writeToFile(Domain domain, Severity severity, const char *fileName,
                      const char *function, int line, const char *message) {
  printer->OpenElement("entry");
    printer->OpenElement("file");
      printer->PushText(fileName);
    printer->CloseElement();
    printer->OpenElement("function");
      printer->PushText(function);
    printer->CloseElement();
    printer->OpenElement("line");
      printer->PushText(line);
    printer->CloseElement();
    printer->OpenElement("domain");
      printer->PushText(DOMAIN_STRINGS[domain]);
    printer->CloseElement();
    printer->OpenElement("severity");
      printer->PushText(SEVERITY_STRINGS[severity]);
    printer->CloseElement();
    printer->OpenElement("message");
      printer->PushText(message);
    printer->CloseElement();
  printer->CloseElement();
  //making sure every entry is in the file before the program crashes
  fflush(file);
}

void Log::preInitWrite(const Log::Entry &entry) {
  if (numPreInitEntries >= MAX_PRE_INIT_ENTRIES) {
    std::cerr << "Too many log entries were written before the logger was initialized\n";
    return;
  }
  
  preInitEntries[numPreInitEntries++] = entry;
}

void Log::flushPreInitEntries() {
  for (size_t i = 0; i < numPreInitEntries; i++) {
    const Entry &entry = preInitEntries[i];
    writeToFile(entry.domain, entry.severity, entry.file,
                entry.function, entry.line, entry.message);
  }
  numPreInitEntries = 0;
}
