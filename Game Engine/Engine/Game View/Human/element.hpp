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
#include "../../Utils/safe down cast.hpp"
#include <glm/mat3x3.hpp>

namespace UI {
  class AmbiguousID final : public std::runtime_error {
  public:
    AmbiguousID(const std::string &, const std::string &);
  };
  
  class BadID final : public std::runtime_error {
  public:
    explicit BadID(const std::string &);
  };
  
  class BadParentPtr final : public std::runtime_error {
  public:
    explicit BadParentPtr(const std::string &);
  };
  
  class BadPolygon final : public std::runtime_error {
  public:
    BadPolygon();
  };
  
  struct Texture {
    explicit Texture(const std::string &, const Trans2D & = {});
  
    std::string path;
    Trans2D transform;
  };
  
  using Textures = std::vector<Texture>;

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
    
    void setTexture(const Texture &);
    void setTexture(size_t, const Texture &);
    void setTexture(const std::string &, const Trans2D & = {});
    void setTexture(size_t, const std::string &, const Trans2D & = {});
    void appendTexture(const std::string &, const Trans2D & = {});
    void setTextures(const Textures &);
    const Textures &getTextures() const;
    
    void addChild(Element::Ptr);
    void remChild(Element::Ptr);
    void remAllChildren();
    const Children &getChildren() const;
    Element::Ptr getChild(const std::string &) const;
    template <typename Derived>
    std::shared_ptr<Derived> getChild(const std::string &id) const {
      return safeDownCast<Derived>(getChild(id));
    }
    Element &getParent() const;
    bool hasParent() const;
    
  protected:
    //@TODO If I never need to access the string ID of an Element I could
    //use a hash of the string instead.
    std::string id;
    AABB bounds;
    //height is relative to the parent. A positive height means that this
    //Element is in front of the parent Element
    Height height = 1;
    Color color = {1.0f, 1.0f, 1.0f, 1.0f};
    Textures textures;
    Children children;
    //if the parent is null, then the parent is the Root
    Element *parent = nullptr;
    bool passthrough = false;
    Polygon hitRegion;
    
    struct MouseData {
      Point relPos;       //the mouse pos in relative space
      Point relParPos;    //the mouse pos relative to parent
      Point absPos;       //the mouse pos in absolute space
      Point relDelta;     //the mouse delta in relative space
      Point relParDelta;  //the mouse delta relative to parent
      Point absDelta;     //the mouse delta in absolute space
      bool down;          //the mouse is down
    };
    
  private:
    virtual void onMouseDown() {}
    virtual void onMouseUp(
      bool    //is the mouse within the bounds of this Element
    ) {}
    virtual void onMouseEnter(
      bool    //is the mouse down
    ) {}
    virtual void onMouseLeave(
      bool    //is the mouse down
    ) {}
    virtual void onMouseMove(
      MouseData
    ) {}
  };
}

#endif
