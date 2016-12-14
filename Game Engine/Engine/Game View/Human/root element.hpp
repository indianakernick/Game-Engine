//
//  root element.hpp
//  Game Engine
//
//  Created by Indi Kernick on 13/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_game_view_human_root_element_hpp
#define engine_game_view_human_root_element_hpp

#include "event.hpp"
#include "element.hpp"
#include "parent element.hpp"

class RootElement : public ParentElement {
friend class Element;
public:
  using Ptr = std::shared_ptr<RootElement>;

  RootElement() = default;
  ~RootElement() = default;
  
  void init();
  void input();
  void update(uint64_t);
  void render();
  void quit();
  
  Element *getFocused();
  
  bool input(Input::Event::Ptr);
private:
  bool propMouse(Input::Event::Ptr);
  void propResize(std::shared_ptr<Input::WindowResize>);

  void handleMouseUp(std::shared_ptr<Input::MouseUp>);
  void handleMouseMove(std::shared_ptr<Input::MouseMove>);
  
  Element *elementWithFocus = nullptr;
  
  Geometry::Point mouseDownPos;
  Input::MButton::Type mouseDownButton;
  Element *mouseDownElement = nullptr;
  bool dragging = false;
  static const int DRAG_THRESHOLD;
  
  std::list<Element *> mouseEntered;
  std::list<Element *> dragEntered;
};

#endif
