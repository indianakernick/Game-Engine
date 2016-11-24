//
//  json.hpp
//  Game Engine
//
//  Created by Indi Kernick on 30/08/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef json_hpp
#define json_hpp

#include <string>
#include <vector>
#include <unordered_map>
#include <assert.h>
#include <fstream>
#include "escape.hpp"

namespace JSON {
  class Var {
  public:
    typedef double Number;
    typedef bool Boolean;
    typedef std::string String;
    typedef std::vector<Var> Array;
    typedef std::unordered_map<std::string, Var> Object;
  
    enum class Type : char {
      number,
      string,
      boolean,
      array,
      object,
      null
    };
    
    union Value {
      Number number;
      Boolean boolean;
      String* string;
      Array* array;
      Object* object;
    };
  
    Var();
    explicit Var(Type);
    Var(Number);
    Var(int);
    Var(Boolean);
    Var(String);
    Var(const char*);
    Var(Array);
    Var(Object);
    Var(std::nullptr_t);
    
    Var(const Var&);
    ~Var();
    
    Var& operator=(Type);
    Var& operator=(Number);
    Var& operator=(int);
    Var& operator=(Boolean);
    Var& operator=(String);
    Var& operator=(const char*);
    Var& operator=(Array);
    Var& operator=(Object);
    Var& operator=(std::nullptr_t);
    
    Var& operator=(const Var&);
    
    Var& operator[](const char*);
    Var& operator[](int);
    
    Type getType();
    
    operator Number&();
    operator Boolean&();
    operator String&();
    
    Number& getNumber();
    Boolean& getBoolean();
    String& getString();
    Array& getArray();
    Object& getObject();
    
    bool operator==(const Var&) const;
    bool operator!=(const Var&) const;
    
    struct Format {
      bool use;
      int indentSize;
      int indent;
    };
    
    void write(std::ofstream&, Format format = {0,0,0});
    static Var read(std::ifstream&);
  private:
    Type type;
    Value value;
    
    void writeArray(std::ofstream&, Format format);
    void writeObject(std::ofstream&, Format format);
    
    void writeArray(std::ofstream&);
    void writeObject(std::ofstream&);
    
    static Var readNumber(std::ifstream&);
    static Var readString(std::ifstream&);
    static Var readArray(std::ifstream&);
    static Var readObject(std::ifstream&);
    
    void destroy();
  };
}

#endif
