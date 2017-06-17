//
//  view impl.hpp
//  Game Engine
//
//  Created by Indi Kernick on 16/6/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef game_view_view_impl_hpp
#define game_view_view_impl_hpp

#include "../../Engine/Application/base.hpp"
#include "../../Engine/Game View/Human/base.hpp"
#include "../../Engine/Game View/Human/root.hpp"
#include "../../Engine/Game View/Human/image.hpp"
#include "../../Engine/Game View/Human/state element.hpp"

namespace Game {
  class ViewImpl final : public HumanView {
  public:
    ViewImpl() = default;
    ~ViewImpl() = default;
    
    void init() override;
    void update(uint64_t) override;
    void quit() override;
    
  private:
    UI::Root::Ptr uiRoot;
    std::weak_ptr<Platform::Window> window;
    Ogre::RenderWindow *renderWindow;
    Ogre::SceneManager *scene;
    Ogre::Camera *camera;
    Ogre::Viewport *viewport;
  };
}

#endif
