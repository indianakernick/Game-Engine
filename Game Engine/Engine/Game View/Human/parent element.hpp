//
//  parent element.hpp
//  Game Engine
//
//  Created by Indi Kernick on 13/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_game_view_human_parent_element_hpp
#define engine_game_view_human_parent_element_hpp

#include <list>
#include <cassert>
#include <memory>

class Element;

class ParentElement {
friend class Element;
friend class RootElement;
public:
  ParentElement() = default;
  virtual ~ParentElement() = default;
  
  void addChild(std::shared_ptr<Element>);
  void remChild(std::shared_ptr<Element>);
protected:
  std::list<std::shared_ptr<Element>> children;

private:
  bool childOrderChanged = false;
  void checkOrderChange();
};

#include "element.hpp"

#endif
