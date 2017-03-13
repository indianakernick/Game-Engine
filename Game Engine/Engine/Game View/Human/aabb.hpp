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
    TOP_RIGHT,
    BOTTOM_RIGHT,
    BOTTOM_LEFT,
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
  };
  
  class AABB {
  friend class AABBStack;
  public:
    void setPos(glm::vec2);
    void setOrigin(Origin, Origin);
    void setOrigin(Origin);
    void setPosSpace(Space);
  
    void setSize(glm::vec2);
    void setAspectRatio(float);
    ///Sets width and calculates height from aspect ratio
    void setWidth(float);
    ///Sets height and calculates width from aspect ratio
    void setHeight(float);
    void setSizeSpace(Space);
    void setSizePropAxis(Axis);
    
    void setSpace(Space);
  private:
    glm::vec2 pos;
    glm::vec2 size;
    float aspectRatio = 1.0f;
    
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
