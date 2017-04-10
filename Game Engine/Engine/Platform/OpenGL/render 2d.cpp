//
//  render 2d.cpp
//  Game Engine
//
//  Created by Indi Kernick on 8/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "render 2d.hpp"

#ifdef USE_OPENGL

using namespace Platform;
using namespace Platform::Render2D;

void ListImpl::push(Texture::Ptr tex, Color color, Height height, Bounds bounds) {
  TextureImpl::Ptr texImpl = std::dynamic_pointer_cast<TextureImpl>(tex);
  assert(texImpl);
  objects.push_back({texImpl, color, height, {
    {bounds[0].x, bounds[0].y},
    {bounds[1].x, bounds[1].y},
    {bounds[2].x, bounds[2].y},
    {bounds[3].x, bounds[3].y}
  }});
}

void ListImpl::zsort() {
  std::sort(objects.begin(), objects.end(), [] (const Object &a, const Object &b) {
    return a.height < b.height;
  });
}

void ListImpl::clear() {
  objects.clear();
}

ContextImpl::ContextImpl(ShaderProgramImpl::Ptr program,
                         VertexArray vao,
                         Buffer pos,
                         Buffer tex,
                         Buffer elem)
  : program(program),
    vao(std::move(vao)),
    pos(std::move(pos)),
    tex(std::move(tex)),
    elem(std::move(elem)),
    texLoc(glGetUniformLocation(program->getID(), "tex")),
    colorLoc(glGetUniformLocation(program->getID(), "color")) {
  assert(program);
  CHECK_OPENGL_ERROR();
}

void ContextImpl::render(const List::Ptr list) {
  const ListImpl::Ptr listImpl = std::dynamic_pointer_cast<ListImpl>(list);
  assert(listImpl);
  
  vao.bind();
  program->bind();
  pos.bind(GL_ARRAY_BUFFER);
  
  glDisable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  
  glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
  glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
  
  //final.rgb = src.rgb * src.a + dst.rgb * (1 - src.a)
  //final.a = src.a * 1 + dst.a * (1 - src.a)
  
  for (auto o = listImpl->objects.cbegin(); o != listImpl->objects.cend(); ++o) {
    glBufferSubData(GL_ARRAY_BUFFER, 0, POS_2D_SIZE * 4, o->bounds);
    glBindTexture(GL_TEXTURE_2D, o->texture->getID());
    glActiveTexture(GL_TEXTURE0);
    setUniform(texLoc, 0);
    setUniform(colorLoc, o->color);
    glDrawElements(GL_TRIANGLES, 6, TypeEnum<ElemType>::type, 0);
  }
  
  CHECK_OPENGL_ERROR();
}

namespace {
  Buffer makePosBuffer() {
    Buffer pos(BIND, GL_ARRAY_BUFFER);
    
    glBufferData(GL_ARRAY_BUFFER, POS_2D_SIZE * 4, nullptr, GL_DYNAMIC_DRAW);
    enablePos2D();
    pos2DPointer(0, 0);
    CHECK_OPENGL_ERROR();
    
    return pos;
  }
  
  Buffer makeTexBuffer() {
    Buffer tex(BIND, GL_ARRAY_BUFFER);
    
    static const TexType texData[4] = {
      {0.0f, 0.0f},//top    left
      {1.0f, 0.0f},//top    right
      {1.0f, 1.0f},//bottom right
      {0.0f, 1.0f} //bottom left
    };
    glBufferData(GL_ARRAY_BUFFER, TEX_SIZE * 4, texData, GL_STATIC_DRAW);
    enableTexturePos();
    texturePosPointer(0, 0);
    CHECK_OPENGL_ERROR();
    
    return tex;
  }
  
  Buffer makeElemBuffer() {
    Buffer elem(BIND, GL_ELEMENT_ARRAY_BUFFER);
    /*
    ┌───┐
    │╲  │
    │ ╲ │
    │  ╲│
    └───┘
    */
    static const ElemType elemData[6] = {
      0, 3, 2, 0, 2, 1
    };
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, ELEM_SIZE * 6, elemData, GL_STATIC_DRAW);
    CHECK_OPENGL_ERROR();
    
    return elem;
  }
}

List::Ptr Platform::Render2D::makeList() {
  return std::shared_ptr<ListImpl>();
}

Context::Ptr Platform::Render2D::makeContext(ShaderProgram::Ptr program) {
  //the vao must be constructed before the makeBuffer functions are called
  //the order of evaluation of function parameters is unspecified
  VertexArray vao(BIND);
  
  return std::make_shared<ContextImpl>(
    std::dynamic_pointer_cast<ShaderProgramImpl>(program),
    std::move(vao),
    makePosBuffer(),
    makeTexBuffer(),
    makeElemBuffer()
  );
}

#endif
