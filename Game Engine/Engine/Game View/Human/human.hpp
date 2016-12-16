//
//  human.hpp
//  Game Engine
//
//  Created by Indi Kernick on 10/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_game_view_human_human_hpp
#define engine_game_view_human_human_hpp

#include "../base.hpp"
#include "root element.hpp"
#include <list>
#include "../../Time/freq limiter.hpp"
#include "../../Input/event listener.hpp"

namespace Game {
  class HumanView : public View,
                    public Input::EventListener {
  public:
    using Ptr = std::shared_ptr<HumanView>;

    HumanView();
    
    virtual void init() override;
    virtual void update(uint64_t) override;
    virtual void render() override;
    virtual Type getType() override;
    
    RootElement::Ptr getRoot();

  protected:
    bool limitRenderFreq = false;
  private:
    RootElement::Ptr root;
    Time::FreqLimiter<std::chrono::milliseconds> limiter;
    
    bool onEvent(Input::Event::Ptr) override;
  };
}

#endif
