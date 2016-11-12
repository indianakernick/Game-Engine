//
//  escape.cpp
//  game engine
//
//  Created by Indi Kernick on 1/09/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "escape.hpp"

std::string Strings::escape(const std::string& str) {
  std::string newStr;
  for (char c : str) {
    switch (c) {
      case '"':
        newStr += "\\\"";
        break;
      case '\'':
        newStr += "\\'";
        break;
      case '\\':
        newStr += "\\\\";
        break;
      case '\n':
        newStr += "\\n";
        break;
      case '\t':
        newStr += "\\t";
        break;
      default:
        if (c < 32 && c >= 0) {
          newStr += '\\' + Math::Format::oct(c);
        } else {
          newStr += c;
        }
    };
  }
  return newStr;
}

std::string Strings::unescape(const std::string& str) {
  std::string newStr;
  //the previous character was a backslash
  bool preBackSlash = false;
  //the previous character was a number preceded by a backspace
  //or a number preceded by a number precended by a backspace etc
  bool preSpecialNum = false;
  std::string specialNum;
  for (char c : str) {
    switch (c) {
      case '\\':
        if (preBackSlash) {
          newStr += '\\';
          preBackSlash = false;
        } else {
          preBackSlash = true;
        }
        break;
      case '"':
        if (preBackSlash) {
          newStr += c;
        } else {
          //oops
          assert(0);
        }
        preBackSlash = false;
        break;
      case '\'':
        if (preBackSlash) {
          newStr += '\'';
        } else {
          //oops
          assert(0);
        }
        preBackSlash = false;
        break;
      case 'n':
        if (preBackSlash) {
          newStr += '\n';
        } else {
          newStr += 'n';
        }
        preBackSlash = false;
        break;
      case 't':
        if (preBackSlash) {
          newStr += '\t';
        } else {
          newStr += 't';
        }
        preBackSlash = false;
        break;
      default:
        if (preBackSlash) {
          if (intChar(c)) {
            preSpecialNum = true;
            specialNum.clear();
            specialNum += c;
          }
        } else if (preSpecialNum) {
          if (intChar(c)) {
            specialNum += c;
          }
          if (!intChar(c) || specialNum.size() == 3) {
            newStr += static_cast<char>(atoi(specialNum.c_str()));
            preSpecialNum = false;
          }
        } else {
          newStr += c;
        }
    }
  }
  return newStr;
}