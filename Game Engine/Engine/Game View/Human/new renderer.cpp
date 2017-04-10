//
//  new renderer.cpp
//  Game Engine
//
//  Created by Indi Kernick on 10/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "new renderer.hpp"

using namespace Platform;
using namespace Platform::Render2D;

const Res::ID UI::NewRenderer::VERT_ID("Shaders/Interpolation/ui.vert");
const Res::ID UI::NewRenderer::FRAG_ID("Shaders/Interpolation/ui.frag");

void UI::NewRenderer::init() {
  renderList = makeList();
  const Shader::Ptr vert = resCache->get<Res::Shader>(VERT_ID)->getShader();
  const Shader::Ptr frag = resCache->get<Res::Shader>(FRAG_ID)->getShader();
  const ShaderProgram::Ptr program = makeShaderProgram("UI", {vert, frag});
  renderContext = makeContext(program);
}

void UI::NewRenderer::render(const Root::Ptr root) {
  renderList->clear();
  const float aspectRatio = Math::aspectRatio<float>(app->window->size());
  AABBStack aabbStack(aspectRatio);
  HeightStack heightStack;
  Element::Children children;
  children.push_back(root->getChild());
  packChildren(aabbStack, heightStack, children);
  renderList->zsort();
  renderContext->render(renderList);
}

void UI::NewRenderer::packChildren(
  AABBStack &aabbStack,
  HeightStack &heightStack,
  const Element::Children &children
) {
  for (auto c = children.begin(); c != children.end(); ++c) {
    const Element::Ptr child = *c;
    aabbStack.push(child->getBounds());
    heightStack.push(child->getHeight());
    packElement(aabbStack.top(), heightStack.top(), child);
    packChildren(aabbStack, heightStack, child->getChildren());
    heightStack.pop();
    aabbStack.pop();
  }
}

void UI::NewRenderer::packElement(SimpleAABB aabb, Height height, const Element::Ptr element) {
  const Res::Texture::Ptr texHandle = resCache->get<Res::Texture>(element->getTexture());
  const Texture::Ptr texture = texHandle->getTexture();
  renderList->push(texture, element->getColor(), height, packBounds(aabb));
}

Bounds UI::NewRenderer::packBounds(SimpleAABB aabb) {
  Bounds bounds;
  bounds[Corner::TL] = aabb.pos;
  bounds[Corner::TR] = {aabb.pos.x + aabb.size.x, aabb.pos.y};
  bounds[Corner::BR] = aabb.pos + aabb.size;
  bounds[Corner::BL] = {aabb.pos.x, aabb.pos.y + aabb.size.y};
  return bounds;
}
