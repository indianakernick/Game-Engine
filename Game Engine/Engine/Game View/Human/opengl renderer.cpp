//
//  opengl renderer.cpp
//  Game Engine
//
//  Created by Indi Kernick on 4/3/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "opengl renderer.hpp"

void UI::RendererOpenGL::init() {
  using namespace Graphics3D;

  LOG_DEBUG(UI, "Initializing OpenGL UI renderer");
  
  ProgType progType;
  progType.ui = true;
  program = std::make_shared<ProgramOpenGL>(progType);
  program->load();
  
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);
  
  glGenBuffers(3, &posBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, posBuffer);
  glBufferData(GL_ARRAY_BUFFER, POS_SIZE * 4, nullptr, GL_STREAM_DRAW);
  enablePos();
  posPointer(0, 0);
  
  static const TexType texData[4] = {
    {0.0f, 1.0f},//top    left
    {1.0f, 1.0f},//top    right
    {1.0f, 0.0f},//bottom right
    {0.0f, 0.0f} //bottom left
  };
  
  glBindBuffer(GL_ARRAY_BUFFER, texBuffer);
  glBufferData(GL_ARRAY_BUFFER, TEX_SIZE * 4, texData, GL_STATIC_DRAW);
  enableTexturePos();
  texturePosPointer(0, 0);
  
  static const ElemType elemData[6] = {
    0, 3, 2, 0, 3, 1
  };
  
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elemBuffer);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, ELEM_SIZE * 6, elemData, GL_STATIC_DRAW);
  
  glBindVertexArray(0);
  
  static const GLfloat defaultTexData[4] = {
    0.0f, 0.0f, 0.0f, 0.0f
  };
  
  glGenTextures(1, &defaultTex);
  glBindTexture(GL_TEXTURE_2D, defaultTex);
  
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_FLOAT, defaultTexData);
  
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  
  texLoc = glGetUniformLocation(program->getID(), "tex");
  colorLoc = glGetUniformLocation(program->getID(), "color");
  assert(texLoc != -1);
  assert(colorLoc != -1);
}

void UI::RendererOpenGL::render(const Root::Ptr root) {
  if (!root->hasChild()) {
    return;
  }
  
  program->bind();
  const float aspectRatio = app->window->getSize().aspect();
  AABBStack aabbStack(aspectRatio);
  HeightStack heightStack;
  Element::Children children;
  children.push_back(root->getChild());
  renderChildren(aabbStack, heightStack, children);
}

void UI::RendererOpenGL::quit() {
  LOG_DEBUG(UI, "Quitting OpenGL UI renderer");
  program.reset();
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
  
  const Res::ID &resID = element->getTexture();
  //have to hold a reference throught the draw call to stop it from being deleted
  Res::TextureOpenGL::Ptr texture;
  GLuint texID;
  if (resID) {
    texture = resCache->get<Res::TextureOpenGL>(resID);
    texID = texture->getID();
  } else {
    texID = defaultTex;
  }
  
  glActiveTexture(GL_TEXTURE0 + DIFF_TEX_UNIT);
  glBindTexture(GL_TEXTURE_2D, texID);
  
  setUniform(texLoc, DIFF_TEX_UNIT);
  setUniform(colorLoc, element->getColor());
  
  glBindVertexArray(vao);
  glDrawElements(GL_TRIANGLES, 2, TypeEnum<ElemType>::type, 0);
}
