//
//  renderer.hpp
//  Game Engine
//
//  Created by Indi Kernick on 15/1/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_3d_opengl_renderer_hpp
#define engine_3d_opengl_renderer_hpp

#ifdef USE_OPENGL

#include "../Scene/renderer.hpp"
#include "../Scene/camera.hpp"
#include "../Scene/light.hpp"
#include "../Scene/mesh.hpp"
#include "program phong.hpp"
#include "program anim.hpp"
#include "../matstack.hpp"
#include "../../Resource/Handles/opengl mesh.hpp"
#include "../../Application/global resource cache.hpp"
#include "../../Resource/shorter namespace.hpp"
#include "../anim.hpp"

namespace Scene {
  class RendererOpenGL : public Renderer {
  public:
    RendererOpenGL() = default;
    ~RendererOpenGL() = default;
  
    void init() override;
    void render(Root::Ptr) override;
    void quit() override;
    
  private:
    Graphics3D::GLProgs::Anim phong;
    Scene::Camera::Ptr camera;
    Graphics3D::MatStack<> stack;
    GLuint vao;
    
    void sendLights(const Scene::Root::Lights &);
    void renderMesh(const Scene::Mesh::Ptr);
    glm::mat4 getAbsTransform(const Scene::Node *);
    void renderChildren(const Scene::Node::Children &);
    void renderNode(const Scene::Node::Ptr);
  };
}

#endif

#endif
