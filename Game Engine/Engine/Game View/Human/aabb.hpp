//
//  ui utils.hpp
//  Game Engine
//
//  Created by Indi Kernick on 1/3/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_game_view_human_aabb_hpp
#define engine_game_view_human_aabb_hpp

#include <glm/vec2.hpp>

namespace UI {
  enum class Origin : uint8_t {
    TOP_LEFT,
    TOP,
    TOP_RIGHT,
    RIGHT,
    BOTTOM_RIGHT,
    BOTTOM,
    BOTTOM_LEFT,
    LEFT,
    CENTER
  };
  
  enum class Space : uint8_t {
    ///Relative to parent
    REL,
    ///Relative to screen
    ABS
  };
  
  enum class Axis : uint8_t {
    ///Both
    BOTH,
    ///Horizontal
    HORI,
    ///Vertical
    VERT,
    ///The longest axis
    MAX,
    ///The shortest axis
    MIN
  };
  
  //I'm beginning to think this should be a struct with a default constructor
  //getters and setters are a bad smell. But size must always be positive.
  //unsigned float...
  
  class AABB {
  friend class AABBStack;
  public:
    AABB() = default;
    ~AABB() = default;
  
    void setPos(glm::vec2);
    void setPos(float, float);
    void setPos(float);
    void setThisOrigin(UI::Origin);
    void setParentOrigin(UI::Origin);
    void setBothOrigin(UI::Origin);
    void setPosSpace(Space);
  
    void setSize(glm::vec2);
    void setSize(float, float);
    void setSize(float);
    void setSizeWidthRatio(float, float);
    void setSizeHeightRatio(float, float);
    void setSizeSpace(Space);
    void setSizeAxis(Axis);
    
    void setSpace(Space);
    
  private:
    glm::vec2 pos;
    glm::vec2 size = {1.0f, 1.0f};
    
    //Offsets are stored as a vector pointing from the parentOrigin to the
    //origin. The parentOrigin may refer to the parent element or the screen
    //depending on the space.
    
    Origin origin = Origin::TOP_LEFT;
    Origin parentOrigin = Origin::TOP_LEFT;
    Space posSpace = Space::REL;
    Space sizeSpace = Space::REL;
    //Proportional axis. The axis which the size is relative to.
    //if size was {0.5f, 0.5f} and axis was HORI then the width would be
    //half of the parent width and the height would be half of the
    //parent width.
    Axis propAxis = Axis::HORI;
  };
};

#endif
