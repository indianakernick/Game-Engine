//
//  opengl renderer.hpp
//  Game Engine
//
//  Created by Indi Kernick on 4/3/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_game_view_human_opengl_renderer_hpp
#define engine_game_view_human_opengl_renderer_hpp

#ifdef USE_OPENGL

#include "renderer.hpp"
#include "../../Utils/logger.hpp"
#include "aabb stack.hpp"
#include "height stack.hpp"
#include "../../Application/base.hpp"
#include "../../3D/OpenGL/program.hpp"
#include "../../3D/OpenGL/attribs.hpp"
#include "../../3D/OpenGL/set uniform.hpp"
#include "root.hpp"
#include "button.hpp"
#include <glm/vec3.hpp>
#include "../../Application/global resource cache.hpp"
#include "../../Resource/Handles/opengl texture.hpp"

namespace UI {
  class RendererOpenGL : public Renderer {
  public:
    void init() override;
    void render(const Root::Ptr) override;
    void quit() override;
  
  private:
    Graphics3D::ProgramOpenGL::Ptr program;
    GLuint posBuffer;
    GLuint texBuffer;
    GLuint elemBuffer;
    GLuint vao;
    GLuint defaultTex;
    GLint texLoc;
    GLint colorLoc;
  
    void renderChildren(AABBStack &, HeightStack &, const Element::Children &);
    void renderElement(const SimpleAABB, const Height, const Element::Ptr);
  };
}

#endif

#endif
