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
#include <string>
#include "types.hpp"
#include "../../Anim/process manager.hpp"

namespace UI {
  class AmbiguousID final : public std::runtime_error {
  public:
    AmbiguousID(const std::string &, const std::string &);
  };
  
  class BadID final : public std::runtime_error {
  public:
    BadID(const std::string &);
  };
  
  class BadParentPtr final : public std::runtime_error {
  public:
    BadParentPtr(const std::string &);
  };
  
  class BadPolygon final : public std::runtime_error {
  public:
    BadPolygon();
  };

  class Element {
  friend class Input;
  public:
    using Ptr = std::shared_ptr<Element>;
    using Children = std::list<Element::Ptr>;
  
    explicit Element(const std::string &);
    virtual ~Element() = default;
    
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
    
    void setTexture(const std::string &texture);
    const std::string &getTexture() const;
    
    void addChild(Element::Ptr);
    void remChild(Element::Ptr);
    void remAllChildren();
    const Children &getChildren() const;
    Element::Ptr getChild(const std::string &) const;
    Element &getParent() const;
    bool hasParent() const;
    
  protected:
    //@TODO If i never need to access the string name of an element I could
    //use a hash of the string instead.
    std::string id;
    AABB bounds;
    //height is relative to the parent. A positive height means that this
    //element is in front of the parent element
    Height height = 1;
    Color color = {1.0f, 1.0f, 1.0f, 1.0f};
    std::string texture;
    Children children;
    //if the parent is null, then the parent is the Root
    Element *parent = nullptr;
    bool passthrough = false;
    Polygon hitRegion;
    
  private:
    virtual void onMouseDown() = 0;
    virtual void onMouseUp(
      bool  //is the mouse within the bounds of this element
    ) = 0;
    virtual void onMouseEnter(
      bool  //is the mouse down
    ) = 0;
    virtual void onMouseLeave(
      bool  //is the mouse down
    ) = 0;
    
    void setProcessManager(ProcessManager *);
  };
}

#endif
