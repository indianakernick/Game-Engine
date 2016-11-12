//
//  ;
//  game engine
//
//  Created by Indi Kernick on 30/08/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "json.hpp"

JSON::Var::Var()
  : type(Type::null) {
  value.number = 0;
}

JSON::Var::Var(Type type) {
  *this = type;
}

JSON::Var::Var(Number number)
  : type(Type::number) {
  value.number = number;
}

JSON::Var::Var(int number)
  : type(Type::number) {
  value.number = number;
}

JSON::Var::Var(Boolean boolean)
  : type(Type::boolean) {
  value.boolean = boolean;
}

JSON::Var::Var(String string)
  : type(Type::string) {
  value.string = new String(string);
}

JSON::Var::Var(const char* string)
  : type(Type::string) {
  value.string = new String(string);
}

JSON::Var::Var(Array array)
  : type(Type::array) {
  value.array = new Array(array);
}

JSON::Var::Var(Object object)
  : type(Type::object) {
  value.object = new Object(object);
}

JSON::Var::Var(std::nullptr_t)
  : type(Type::null) {
  value.number = 0;
}

JSON::Var::Var(const JSON::Var& other)
  : type(other.type) {
  switch (type) {
    case Type::number:
    case Type::boolean:
    case Type::null:
      value.number = other.value.number;
      break;
    case Type::string:
      value.string = new String(*other.value.string);
      break;
    case Type::array:
      value.array = new Array(*other.value.array);
      break;
    case Type::object:
      value.object = new Object(*other.value.object);
  }
}

JSON::Var::~Var() {
  destroy();
}

JSON::Var& JSON::Var::operator=(Type type) {
  destroy();
  switch (type) {
    case Type::number:
    case Type::boolean:
    case Type::null:
      value.number = 0;
      break;
    case Type::string:
      value.string = new String;
      break;
    case Type::object:
      value.object = new Object;
      break;
    case Type::array:
      value.array = new Array;
  }
  this->type = type;
  return *this;
}

JSON::Var& JSON::Var::operator=(Number number) {
  destroy();
  type = Type::number;
  value.number = number;
  return *this;
}

JSON::Var& JSON::Var::operator=(int number) {
  destroy();
  type = Type::number;
  value.number = number;
  return *this;
}

JSON::Var& JSON::Var::operator=(Boolean boolean) {
  destroy();
  type = Type::boolean;
  value.boolean = boolean;
  return *this;
}

JSON::Var& JSON::Var::operator=(String string) {
  destroy();
  type = Type::string;
  value.string = new String(string);
  return *this;
}

JSON::Var& JSON::Var::operator=(const char* string) {
  destroy();
  type = Type::string;
  value.string = new String(string);
  return *this;
}

JSON::Var& JSON::Var::operator=(Array array) {
  destroy();
  type = Type::array;
  value.array = new Array(array);
  return *this;
}

JSON::Var& JSON::Var::operator=(Object object) {
  destroy();
  type = Type::object;
  value.object = new Object(object);
  return *this;
}

JSON::Var& JSON::Var::operator=(std::nullptr_t) {
  destroy();
  type = Type::object;
  return *this;
}

JSON::Var& JSON::Var::operator=(const JSON::Var& other) {
  type = other.type;
  switch (type) {
    case Type::number:
    case Type::boolean:
    case Type::null:
      value.number = other.value.number;
      break;
    case Type::string:
      value.string = new String(*other.value.string);
      break;
    case Type::array:
      value.array = new Array(*other.value.array);
      break;
    case Type::object:
      value.object = new Object(*other.value.object);
  }
  return *this;
}

JSON::Var& JSON::Var::operator[](const char* key) {
  if (type != Type::object) {
    *this = Type::object;
  }
  return (*value.object)[key];
}

JSON::Var& JSON::Var::operator[](int key) {
  if (type != Type::array) {
    *this = Type::array;
  }
  return (*value.array)[key];
}

JSON::Var::Type JSON::Var::getType() {
  return type;
}

JSON::Var::operator Number&() {
  assert(type == Type::number);
  return value.number;
}

JSON::Var::operator Boolean&() {
  assert(type == Type::boolean);
  return value.boolean;
}

JSON::Var::operator String&() {
  assert(type == Type::string);
  return *value.string;
}

JSON::Var::Number& JSON::Var::getNumber() {
  assert(type == Type::number);
  return value.number;
}

JSON::Var::Boolean& JSON::Var::getBoolean() {
  assert(type == Type::boolean);
  return value.boolean;
}

JSON::Var::String& JSON::Var::getString() {
  assert(type == Type::string);
  return *value.string;
}

JSON::Var::Array& JSON::Var::getArray() {
  assert(type == Type::array);
  return *value.array;
}

JSON::Var::Object& JSON::Var::getObject() {
  assert(type == Type::object);
  return *value.object;
}

bool JSON::Var::operator==(const JSON::Var& other) const {
  if (type == other.type) {
    switch (type) {
      case Type::number:
        return value.number == other.value.number;
      case Type::boolean:
        return value.boolean == other.value.boolean;
      case Type::string:
        return *value.string == *other.value.string;
      case Type::array:
        return *value.array == *other.value.array;
      case Type::object:
        return *value.object == *other.value.object;
      case Type::null:
        return true;
    }
  } else {
    return false;
  }
}

bool JSON::Var::operator!=(const JSON::Var& other) const {
  return !(*this == other);
}

void JSON::Var::write(std::ofstream& file, Format format) {
  assert(file.is_open());
  switch (type) {
    case Type::number:
      file << value.number;
      break;
    case Type::boolean:
      file << (value.boolean ? "true" : "false");
      break;
    case Type::string:
      file << '"';
      file << Strings::escape(*value.string);
      file << '"';
      break;
    case Type::array:
      if (format.use) {
        writeArray(file, format);
      } else {
        writeArray(file);
      }
      break;
    case Type::object:
      if (format.use) {
        writeObject(file, format);
      } else {
        writeObject(file);
      }
      break;
    case Type::null:
      file << "null";
  }
}

JSON::Var JSON::Var::read(std::ifstream& file) {
  GET_CHAR:
  char c = file.get();
  switch (c) {
    case EOF:
      return nullptr;
    case '\t':
    case '\n':
    case ' ':
      goto GET_CHAR;
    case 't':
      file.seekg(3, std::ios::cur);
      return true;
    case 'f':
      file.seekg(4, std::ios::cur);
      return false;
    case 'n':
      file.seekg(3, std::ios::cur);
      return nullptr;
    case '"':
      file.seekg(-1, std::ios::cur);
      return readString(file);
    case '[':
      file.seekg(-1, std::ios::cur);
      return readArray(file);
    case '{':
      file.seekg(-1, std::ios::cur);
      return readObject(file);
    
    default:
      if (Strings::floatChar(c)) {
        file.seekg(-1, std::ios::cur);
        return readNumber(file);
      } else {
        return nullptr;
      }
  }
}

void JSON::Var::writeArray(std::ofstream& file, Format format) {
  file << "[\n";
  format.indent++;
  std::string indentStr(format.indent * format.indentSize, ' ');
  for (size_t i = 0; i < value.array->size(); i++) {
    file << indentStr;
    (*value.array)[i].write(file, format);
    if (i < value.array->size() - 1) {
      file << ',';
    }
    file << '\n';
  }
  format.indent--;
  file << std::string(format.indent * format.indentSize, ' ') << ']';
}

void JSON::Var::writeObject(std::ofstream& file, Format format) {
  file << "{\n";
  format.indent++;
  std::string indentStr(format.indent * format.indentSize, ' ');
  for (auto i = value.object->begin(); i != value.object->end(); ++i) {
    file << indentStr << '"' << Strings::escape(i->first) << "\": ";
    i->second.write(file, format);
    auto j = i;
    if (++j != value.object->end()) {
      file << ',';
    }
    file << '\n';
  }
  format.indent--;
  file << std::string(format.indent * format.indentSize, ' ') << '}';
}

void JSON::Var::writeArray(std::ofstream& file) {
  file << '[';
  for (size_t i = 0; i < value.array->size(); i++) {
    (*value.array)[i].write(file, {0,0,0});
    if (i < value.array->size() - 1) {
      file << ',';
    }
  }
  file << ']';
}

void JSON::Var::writeObject(std::ofstream& file) {
  file << '{';
  for (auto i = value.object->begin(); i != value.object->end(); ++i) {
    file << '"' << Strings::escape(i->first) << "\":";
    i->second.write(file, {0,0,0});
    auto j = i;
    if (++j != value.object->end()) {
      file << ',';
    }
  }
  file << '}';
}

JSON::Var JSON::Var::readNumber(std::ifstream& file) {
  std::string str;
  char c = file.get();
  while (Strings::floatChar(c)) {
    str += c;
    c = file.get();
  }
  file.seekg(-1, std::ios::cur);
  return atof(str.c_str());
}

JSON::Var JSON::Var::readString(std::ifstream& file) {
  std::string str;
  char c = file.get();
  if (c != '"') {
    return nullptr;
  }
  c = file.get();
  bool preBackSlash = false;
  while (true) {
    if (!preBackSlash && c == '"') {
      break;
    }
    str += c;
    preBackSlash = (c == '\\');
    c = file.get();
  }
  return Strings::unescape(str);
}

JSON::Var JSON::Var::readArray(std::ifstream& file) {
  char c = file.get();
  if (c != '[') {
    return nullptr;
  }
  Var array = Var(Type::array);
  while (true) {
    array.value.array->push_back(read(file));
    bool comma = false;
    GET_CHAR:
    c = file.get();
    switch (c) {
      case EOF:
        return nullptr;
      case ',':
        comma = true;
        //no break
      case ' ':
      case '\n':
      case '\t':
        goto GET_CHAR;
      case ']':
        return array;
      default:
        if (comma) {
          file.seekg(-1, std::ios::cur);
        } else {
          return nullptr;
        }
    }
  }
}

JSON::Var JSON::Var::readObject(std::ifstream& file) {
  char c = file.get();
  if (c != '{') {
    return nullptr;
  }
  Var object = Var(Type::object);
  while (true) {
    Var key = read(file);
    if (key.type != Type::string) {
      return nullptr;
    }
    bool colon = false;
    GET_CHAR0:
    c = file.get();
    //we have the key, we're expecting a value
    switch (c) {
      case EOF:
        return nullptr;
      case ':':
        colon = true;
      case ' ':
      case '\n':
      case '\t':
        goto GET_CHAR0;
      case '}':
        return nullptr;
      default:
        if (colon) {
          file.seekg(-1, std::ios::cur);
        } else {
          return nullptr;
        }
    }
    object[(*key.value.string).c_str()] = read(file);
    bool comma = false;
    GET_CHAR1:
    c = file.get();
    //we have the key and value.
    //if theres a ',' we expect another key and value
    //if theres a '}' we're done
    switch (c) {
      case EOF:
        return nullptr;
      case ',':
        comma = true;
      case ' ':
      case '\n':
      case '\t':
        goto GET_CHAR1;
      case '}':
        return object;
      default:
        if (comma) {
          file.seekg(-1, std::ios::cur);
        } else {
          return nullptr;
        }
    }
  }
}

void JSON::Var::destroy() {
  //not sure if this matters
  switch (type) {
    case Type::string:
      delete value.string;
      break;
    case Type::object:
      delete value.object;
      break;
    case Type::array:
      delete value.array;
    default: ;
  };
  value.number = 0;
}