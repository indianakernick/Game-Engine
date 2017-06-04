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
#include "types.hpp"
#include <glm/mat3x3.hpp>
#include "../../Utils/dispatcher.hpp"
#include "../../Utils/safe down cast.hpp"
#include "events.hpp"
#include "node.hpp"

namespace UI {
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

  class Element : public Node<Element> {
  private:
    using EventDispatcher = GroupDispatcher<void (const Event::Ptr), void, Event::Type, uint32_t>;
    
  public:
    using Ptr = std::shared_ptr<Element>;
    using Children = std::list<Element::Ptr>;
    using Listener = EventDispatcher::Listener;
    using ListenerID = EventDispatcher::ListenerID;
  
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
    
    void setTexture(const Texture &, size_t = 0);
    void setTexture(const std::string &, const Trans2D & = {}, size_t = 0);
    void appendTexture(const Texture &);
    void appendTexture(const std::string &, const Trans2D & = {});
    void setTextures(const Textures &);
    const Textures &getTextures() const;
  
    virtual ListenerID addListener(Event::Type, const Listener &);
    void remListener(ListenerID);
    void dispatchEvent(Event::Type, Event::Ptr);
    
    template <typename EventClass, typename ...Args>
    void dispatchEvent(Args &&... args) {
      dispatchEvent(
        EventType<EventClass>::get(),
        std::make_shared<EventClass>(std::forward<Args>(args)...)
      );
    }
    
    template <typename EventClass>
    ListenerID addListener(const std::function<void (std::shared_ptr<EventClass>)> &listener) {
      return addListener(
        EventType<EventClass>::get(),
        [listener] (const Event::Ptr event) {
          listener(safeDownCast<EventClass>(event));
        }
      );
    }
    
    template <typename EventClass>
    ListenerID addListener(std::function<void (std::shared_ptr<EventClass>)> &&listener) {
      return addListener(
        EventType<EventClass>::get(),
        [listener = std::move(listener)] (const Event::Ptr event) {
          listener(safeDownCast<EventClass>(event));
        }
      );
    }
    
  protected:
    EventDispatcher dispatcher;
    AABB bounds;
    //height is relative to the parent. A positive height means that this
    //Element is in front of the parent Element
    Height height = 1;
    Color color = {1.0f, 1.0f, 1.0f, 1.0f};
    Textures textures;
    Polygon hitRegion;
    bool passthrough = false;
  };
}

#endif
