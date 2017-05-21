//
//  human view impl.hpp
//  Game Engine
//
//  Created by Indi Kernick on 24/1/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef game_human_view_impl_hpp
#define game_human_view_impl_hpp

#include "../Engine/Game View/Human/base.hpp"
#include "../Engine/Application/base.hpp"
#include "../Engine/Game View/Human/root.hpp"
#include "../Engine/Game View/Human/button.hpp"
#include "../Engine/Game View/Human/image.hpp"
#include "../Engine/Game View/Human/checkbox.hpp"

namespace Game {
  class HumanViewImpl final : public HumanView {
  public:
    HumanViewImpl() = default;
    ~HumanViewImpl() = default;
    
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
    Ogre::SceneNode *ogrehead;
  };
}

#endif
