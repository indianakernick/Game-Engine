//
//  root.hpp
//  Game Engine
//
//  Created by Indi Kernick on 11/3/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_game_view_human_root_hpp
#define engine_game_view_human_root_hpp

#include "element.hpp"

namespace UI {
  class Root final {
  public:
    using Ptr = std::shared_ptr<Root>;
    
    Root() = default;
    ~Root() = default;
    
    void setChild(Element::Ptr);
    void unSetChild();
    Element::Ptr getChild() const;
    bool hasChild() const;
  
  private:
    Element::Ptr child;
  };
}

#endif
