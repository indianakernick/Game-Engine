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
#include "input.hpp"
#include "renderer.hpp"

namespace UI {
  class Root {
  public:
    using Ptr = std::unique_ptr<Root>;
    
    Root(
      std::weak_ptr<Platform::Window>,
      Ogre::Viewport *,
      Ogre::SceneManager *
    );
    ~Root() = default;
    
    void setChild(Element::Ptr, const std::string &, const std::string &);
    void unSetChild();
    Element::Ptr getChild() const;
    bool hasChild() const;
  
  private:
    Element::Ptr child;
    Input input;
    Renderer renderer;
  };
}

#endif
