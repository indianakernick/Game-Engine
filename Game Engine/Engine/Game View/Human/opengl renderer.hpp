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
#include "../../3D/OpenGL/attribs.hpp"
#include "../../3D/OpenGL/set uniform.hpp"
#include "root.hpp"
#include <glm/vec3.hpp>
#include "../../Application/global resource cache.hpp"
#include "../../Resource/Handles/opengl texture.hpp"
#include "../../3D/OpenGL/program manager.hpp"

namespace UI {
  class RendererOpenGL : public Renderer {
  public:
    void init(Graphics3D::ProgramManager::Ptr) override;
    void render(const Root::Ptr) override;
    void quit() override;
  
  private:
    static const Graphics3D::ProgType UI_PROG;
    
    ///All the data needed to draw an element
    struct DrawData {
      DrawData(const Res::ID &, const glm::vec4 &, Height);
    
      Res::ID texture;
      glm::vec4 color;
      Graphics3D::Pos2DType bounds[4];
      Height height;
    };
    
    std::vector<DrawData> drawData;
  
    Graphics3D::ProgramManagerOpenGL::Ptr progMan;
    GLuint posBuffer;
    GLuint texBuffer;
    GLuint elemBuffer;
    GLuint vao;
  
    void packChildren(AABBStack &, HeightStack &, const Element::Children &);
    void packElement(const SimpleAABB, const Height, const Element::Ptr);
    void sortElements();
    void renderElements();
  };
}

#endif

#endif
