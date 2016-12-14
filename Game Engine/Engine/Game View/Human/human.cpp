//
//  human.cpp
//  Game Engine
//
//  Created by Indi Kernick on 10/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "human.hpp"

void HumanView::init() {
  root->init();
}

void HumanView::update(uint64_t delta) {
  root->input();
  root->update(delta);
}

void HumanView::render() {
  if (limitRenderFreq && !limiter.canDo()) {
    return;
  }
  root->render();
}

bool HumanView::onInput(Input::Event::Ptr event) {
  return root->input(event);
}
