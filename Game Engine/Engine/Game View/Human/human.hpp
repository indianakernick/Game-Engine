//
//  human.hpp
//  Game Engine
//
//  Created by Indi Kernick on 10/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_game_view_human_human_hpp
#define engine_game_view_human_human_hpp

#include "base.hpp"
#include "root element.hpp"
#include <list>
#include "../../Time/freq limiter.hpp"

class HumanView : public GameView {
public:
  using Ptr = std::shared_ptr<HumanView>;

  HumanView() = default;
  
  virtual void init() override;
  virtual void update(uint64_t) override;
  virtual void render() override;
  virtual bool onInput(Input::Event::Ptr) override;
  
  RootElement::Ptr getRoot();

protected:
  bool limitRenderFreq = false;
private:
  RootElement::Ptr root;
  Time::FreqLimiter<std::chrono::milliseconds> limiter;
};

#endif
