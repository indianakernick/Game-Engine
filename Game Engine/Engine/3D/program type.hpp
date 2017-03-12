//
//  program type.hpp
//  Game Engine
//
//  Created by Indi Kernick on 12/3/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_3d_program_type_hpp
#define engine_3d_program_type_hpp

#include <cstdint>
#include <functional>
#include "../Utils/combine.hpp"

namespace Graphics3D {
  ///The same as the aiShadingMode enum from ASSIMP
  enum class FragType : uint8_t {
    SOLID,
    PHONG,
    BLINN,
    COOK_TORRANCE,
    TOON,
    OREN_NAYER,
    MINNAERT,
    FRESNEL,
    
    _COUNT = 4
  };
  
  ///Identifies a shader program
  struct ProgType {
    bool anim;
    FragType frag;
    bool ui = false;
    
    bool operator==(ProgType other) const;
    bool operator!=(ProgType other) const;
  };
}

template <>
struct std::hash<Graphics3D::ProgType> {
  size_t operator()(const Graphics3D::ProgType) const;
};

#endif
