//
//  element.hpp
//  Game Engine
//
//  Created by Indi Kernick on 1/3/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_game_view_human_element_hpp
#define engine_game_view_human_element_hpp

#include "aabb.hpp"
#include <memory>
#include <list>
#include <glm/vec4.hpp>
#include "../../Resource/id.hpp"

namespace UI {
  using Height = int;
  using Color = glm::vec4;

  class Element {
  friend class Renderer;
  public:
    using Ptr = std::shared_ptr<Element>;
    using Children = std::list<Element::Ptr>;
  
    Element() = default;
    virtual ~Element() = default;
    
    virtual const Res::ID &getTexture() const = 0;
    
    const AABB &getBounds() const;
    
    void setHeight(Height);
    Height getHeight() const;
    
    void setColor(const Color &);
    const Color &getColor() const;
    
    void addChild(Element::Ptr);
    void remChild(Element::Ptr);
    void remAllChildren();
    const Children &getChildren() const;
    Element &getParent() const;
    bool hasParent() const;
    
  protected:
    AABB bounds;
    //height is relative to the parent. A positive height means that this
    //element is in front of the parent element
    Height height = 1;
    Color color;
    Children children;
    //if the parent is null, then the parent is the Root
    Element *parent = nullptr;
  };
}

#endif
