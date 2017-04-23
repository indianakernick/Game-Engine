//
//  base.hpp
//  Game Engine
//
//  Created by Indi Kernick on 10/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_game_view_human_base_hpp
#define engine_game_view_human_base_hpp

#include "../base.hpp"
#include "../../Anim/process manager.hpp"
#include "../../Application/ogre.pch"
#include "../../Platform/Interface/window library.hpp"

namespace Game {
  class HumanView : public View {
  public:
    using Ptr = std::shared_ptr<HumanView>;

    HumanView();
    virtual ~HumanView() = default;
    
    virtual void init() override;
    virtual void update(uint64_t) override;
    virtual void render() override;
    virtual void quit() override;
    Type getType() override final;
    
  protected:
    ProcessManager processManager;
  };
}

#endif
