//
//  opengl renderer.cpp
//  Game Engine
//
//  Created by Indi Kernick on 4/3/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "opengl renderer.hpp"

const Graphics3D::ProgType UI::RendererOpenGL::UI_PROG = {false, Graphics3D::FragType::SOLID, true};

void UI::RendererOpenGL::init(Graphics3D::ProgramManager::Ptr progManBase) {
  using namespace Graphics3D;

  PROFILE(UI renderer init);

  LOG_DEBUG(UI, "Initializing OpenGL UI renderer");
  
  progMan = std::dynamic_pointer_cast<ProgramManagerOpenGL>(progManBase);
  assert(progMan);
  
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);
  
  glGenBuffers(3, &posBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, posBuffer);
  glBufferData(GL_ARRAY_BUFFER, POS_SIZE * 4, nullptr, GL_DYNAMIC_DRAW);
  enablePos();
  posPointer(0, 0);
  
  static const TexType texData[4] = {
    {0.0f, 0.0f},//top    left
    {1.0f, 0.0f},//top    right
    {1.0f, 1.0f},//bottom right
    {0.0f, 1.0f} //bottom left
  };
  
  glBindBuffer(GL_ARRAY_BUFFER, texBuffer);
  glBufferData(GL_ARRAY_BUFFER, TEX_SIZE * 4, texData, GL_STATIC_DRAW);
  enableTexturePos();
  texturePosPointer(0, 0);
  
  static const ElemType elemData[6] = {
    0, 3, 2, 0, 2, 1
  };
  
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elemBuffer);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, ELEM_SIZE * 6, elemData, GL_STATIC_DRAW);
  
  glBindVertexArray(0);
  
  CHECK_OPENGL_ERROR();
}

void UI::RendererOpenGL::render(const Root::Ptr root) {
  PROFILE(UI renderer render);

  if (!root->hasChild()) {
    return;
  }
  
  glEnable(GL_BLEND);
  
  glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
  glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
  
  //final.rgb = src.rgb * src.a + dst.rgb * (1 - src.a)
  //final.a = src.a * 1 + dst.a * (1 - src.a)
  
  glClear(GL_DEPTH_BUFFER_BIT);
  
  glBindVertexArray(vao);
  
  progMan->bind(UI_PROG);
  const float aspectRatio = app->window->getSize().aspect();
  AABBStack aabbStack(aspectRatio);
  HeightStack heightStack;
  Element::Children children;
  children.push_back(root->getChild());
  renderChildren(aabbStack, heightStack, children);
  
  glDisable(GL_BLEND);
  
  CHECK_OPENGL_ERROR();
}

void UI::RendererOpenGL::quit() {
  LOG_DEBUG(UI, "Quitting OpenGL UI renderer");
}

void UI::RendererOpenGL::renderChildren(AABBStack &aabbStack,
                                        HeightStack &heightStack,
                                        const Element::Children &children) {
  for (auto c = children.begin(); c != children.end(); ++c) {
    const Element::Ptr child = *c;
    aabbStack.push(child->getBounds());
    heightStack.push(child->getHeight());
    renderElement(aabbStack.top(), heightStack.top(), child);
    renderChildren(aabbStack, heightStack, child->getChildren());
    heightStack.pop();
    aabbStack.pop();
  }
}

inline void assign(Graphics3D::PosType &a, const glm::vec2 &b) {
  a[0] = b[0];
  a[1] = b[1];
}

void packPosData(Graphics3D::PosType (&posData)[4],
                 const UI::SimpleAABB bounds,
                 const UI::Height height) {
  assign(posData[0], bounds.pos);                                  //top left
  assign(posData[1], {bounds.pos.x + bounds.size.x, bounds.pos.y});//top right
  assign(posData[2], bounds.pos + bounds.size);                    //bottom right
  assign(posData[3], {bounds.pos.x, bounds.pos.y + bounds.size.y});//bottom left
  posData[0][2] = height;
  posData[1][2] = height;
  posData[2][2] = height;
  posData[3][2] = height;
}

void UI::RendererOpenGL::renderElement(const SimpleAABB bounds,
                                       const Height height,
                                       const Element::Ptr element) {
  using namespace Graphics3D;
  
  PosType posData[4];
  packPosData(posData, bounds, height);
  
  glBindBuffer(GL_ARRAY_BUFFER, posBuffer);
  glBufferSubData(GL_ARRAY_BUFFER, 0, POS_SIZE * 4, posData);
  
  progMan->setMaterial(element->getColor(), element->getTexture());
  
  glDrawElements(GL_TRIANGLES, 6, TypeEnum<ElemType>::type, 0);
  
  CHECK_OPENGL_ERROR();
}
