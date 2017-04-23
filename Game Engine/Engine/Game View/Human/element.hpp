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
#include <vector>
#include <string>

namespace UI {
  using Height = int;
  using Color = glm::vec4;
  using Polygon = std::vector<glm::vec2>;

  class Element {
  friend class Input;
  public:
    using Ptr = std::shared_ptr<Element>;
    using Children = std::list<Element::Ptr>;
  
    Element() = default;
    virtual ~Element() = default;
    
    virtual const std::string &getTexture() const = 0;
    
    void setBounds(const AABB &);
    const AABB &getBounds() const;
    
    void setHitRegion(const Polygon &);
    void unsetHitRegion();
    const Polygon &getHitRegion() const;
    bool hasHitRegion() const;
    
    void setHeight(Height);
    Height getHeight() const;
    
    void setPassthrough(bool);
    bool getPassthrough() const;
    
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
    Color color = {1.0f, 1.0f, 1.0f, 1.0f};
    Children children;
    //if the parent is null, then the parent is the Root
    Element *parent = nullptr;
    bool passthrough = false;
    Polygon hitRegion;
    
  private:
    virtual void onMouseDown() = 0;
    virtual void onMouseUp(bool within) = 0;
    virtual void onMouseEnter(bool mouseDown) = 0;
    virtual void onMouseLeave(bool mouseDown) = 0;
  };
}

#endif
