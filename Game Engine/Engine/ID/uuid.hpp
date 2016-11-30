//
//  uuid.hpp
//  Game Engine
//
//  Created by Indi Kernick on 11/08/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_id_uuid_hpp
#define engine_id_uuid_hpp

#include <random>
#include <string>

namespace ID {
  ///Each instance is a variant 4 UUID
  class UUID {
  public:
    UUID();
    explicit UUID(std::string);
    explicit UUID(std::nullptr_t);
  
    bool operator==(const UUID&);
    bool operator!=(const UUID&);
    
    std::string display();
  private:
    static std::random_device gen;
    static std::uniform_int_distribution<uint64_t> dist;
    //clears the bits where the varient should go
    static const uint64_t clearHi;
    //clears the reserved bits
    static const uint64_t clearLo;
    //puts the varient number in the area cleared
    static const uint64_t varient;
    //the reerved bits
    static const uint64_t reserve;
    //the left part
    uint64_t hi;
    //the right part
    uint64_t lo;
  };
};

#endif
