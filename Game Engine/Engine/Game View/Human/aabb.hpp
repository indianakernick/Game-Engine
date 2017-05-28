//
//  ui utils.hpp
//  Game Engine
//
//  Created by Indi Kernick on 1/3/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_game_view_human_aabb_hpp
#define engine_game_view_human_aabb_hpp

#include "types.hpp"

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
  
  class BadBounds final : public std::runtime_error {
  public:
    explicit BadBounds(const std::string &);
  };
  
  class AABB {
  public:
    AABB() = default;
    ~AABB() = default;
  
    void pos(Point);
    void pos(Coord);
    void thisOrigin(UI::Origin);
    void parentOrigin(UI::Origin);
    void bothOrigin(UI::Origin);
    void posSpace(Space);
  
    void size(Point);
    void size(Coord);
    void widthAndRatio(Coord, Coord);
    void heightAndRatio(Coord, Coord);
    void sizeSpace(Space);
    void sizeAxis(Axis);
    
    void space(Space);
    
    Point  pos         () const;
    Point  size        () const;
    Coord  width       () const;
    Coord  height      () const;
    Origin thisOrigin  () const;
    Origin parentOrigin() const;
    Space  posSpace    () const;
    Space  sizeSpace   () const;
    Axis   sizeAxis    () const;
    
  private:
    Point mPos;
    Point mSize = {1.0f, 1.0f};
    
    //Offsets are stored as a vector pointing from the parentOrigin to
    //thisOrigin. The parentOrigin may refer to the parent element or the screen
    //depending on the space.
    
    Origin mThisOrigin = Origin::TOP_LEFT;
    Origin mParentOrigin = Origin::TOP_LEFT;
    
    Space mPosSpace = Space::REL;
    Space mSizeSpace = Space::REL;
    
    //The axis which the size is relative to.
    //if size was {0.5f, 0.5f} and axis was HORI then the width would be
    //half of the parent width and the height would be half of the
    //parent width.
    Axis mSizeAxis = Axis::HORI;
  };
};

#endif
