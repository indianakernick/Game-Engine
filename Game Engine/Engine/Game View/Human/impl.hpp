//
//  impl.hpp
//  Game Engine
//
//  Created by Indi Kernick on 24/1/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_game_view_human_impl_hpp
#define engine_game_view_human_impl_hpp

#include "base.hpp"
#include "../../Input/Listeners/mouseless fly camera controller.hpp"
#include "../../3D/anim.hpp"
#include "button.hpp"
#include "checkbox.hpp"
#include "image.hpp"

namespace Game {
  class HumanViewImpl : public HumanView {
  public:
    HumanViewImpl() = default;
    ~HumanViewImpl() = default;
    
    void init() override;
    void update(uint64_t) override;
    void quit() override;
  private:
    Scene::Camera::Ptr camera;
    CamControlFlyMouseless::Ptr controller;
  };
}

#endif
