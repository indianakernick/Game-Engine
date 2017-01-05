//
//  root node.cpp
//  Game Engine
//
//  Created by Indi Kernick on 19/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "root node.hpp"

Graphics3D::RootNode::RootNode()
  : SceneNode(Game::Actor::NULL_ID, PASS_FIRST, {}, 0.0f) {
  children.reserve(PASS_LAST);
  
  for (int p = PASS_FIRST; p < PASS_LAST; p++) {
    children.push_back(std::make_shared<SceneNode>(Game::Actor::NULL_ID,
                                                   static_cast<RenderPass>(p),
                                                   glm::mat4(),
                                                   0.0f));
  }
}

bool Graphics3D::RootNode::isVisible(Scene *) const {
  return true;
}

void Graphics3D::RootNode::renderChildren(Scene *scene) {
  for (int p = PASS_FIRST; p < PASS_LAST; p++) {
    switch (p) {
      case PASS_STATIC:
      case PASS_DYNAMIC:
        children[p]->renderChildren(scene);
        break;
      case PASS_SKY:
        //set up context for sky
        children[p]->renderChildren(scene);
        //restore context
        break;
    }
  }
}

void Graphics3D::RootNode::addChild(SceneNode::Ptr node) {
  children[static_cast<int>(node->getProp().getPass())]->addChild(node);
}
