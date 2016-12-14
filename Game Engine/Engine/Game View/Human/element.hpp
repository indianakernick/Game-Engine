//
//  element.hpp
//  Game Engine
//
//  Created by Indi Kernick on 13/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_game_view_human_element_hpp
#define engine_game_view_human_element_hpp

#include <memory>
#include "../../Geometry/rect.hpp"
#include "../../Input/event.hpp"
#include "event.hpp"
#include "event element.hpp"
#include "parent element.hpp"

class RootElement;

class Element : private EventElement,
                public ParentElement {
friend class ParentElement;
friend class RootElement;
public:
  using Ptr = std::shared_ptr<Element>;
  
  Element() = default;
  virtual ~Element() = default;
  
  bool isVisible() const;
  void setVisible(bool);
  void show();
  void hide();
  
  int getOrder() const;
  void setOrder(int);
  
  bool hasFocus() const;
  void focus();
  
  Geometry::Rect getBounds() const;
  
  Element::Ptr getPtr();
protected:
  Geometry::Rect bounds;
  
  virtual void onInit() = 0;
  virtual void onUpdate(uint64_t) = 0;
  virtual void onRender(Geometry::Point) = 0;
  virtual void onQuit() = 0;
  virtual bool canHandleScroll(Geometry::Point) const;
  //is this element draggable
  virtual bool draggable() const;
  //is this element droppable onto some other element
  virtual bool droppable(Element *) const;
  
  using EventElement::addEventListener;
  using EventElement::remEventListener;
private:
  void init();
  void input();
  void update(uint64_t);
  void render(Geometry::Point);
  void quit();
  
  //root or another element
  ParentElement *parent = nullptr;
  
  void changeFocus(Element *);
  //propagate up to the root and return the elementWithFocus
  Element *getFocus();
  //this element has focus
  bool focused = false;
  
  RootElement *getRoot();
  const RootElement *getRoot() const;
  
  bool visible = true;
  int order = 0;
  
  //propagate a mouse event
  bool propMouse(Input::Event::Ptr);
  //propagate window resize event
  void propResize(std::shared_ptr<Events::WindowResize>);
  
  bool handleEvent(Input::Event::Ptr);
  bool handleMouseDown(std::shared_ptr<Input::MouseDown>);
  bool handleMouseUp(std::shared_ptr<Input::MouseUp>);
  bool handleMouseMove(std::shared_ptr<Input::MouseMove>);
  bool handleScroll(std::shared_ptr<Input::Scroll>);
  
  //key events are only handled by the element with focus
  //if there isn't one then key events will go to the key handlers
  void handleKeyDown(std::shared_ptr<Input::KeyDown>);
  void handleKeyUp(std::shared_ptr<Input::KeyUp>);
  
  Geometry::Point absToRel(Geometry::Point abs);
  Geometry::Point absToRelParent(Geometry::Point abs);
  
  Geometry::Point relToAbs(Geometry::Point rel);
  Geometry::Point relParentToAbs(Geometry::Point relParent);
  
  Geometry::Point relToRelParent(Geometry::Point rel);
  Geometry::Point relParentToRel(Geometry::Point relParent);
};

#include "root element.hpp"

#endif
