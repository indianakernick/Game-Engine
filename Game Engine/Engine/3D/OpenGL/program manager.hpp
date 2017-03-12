//
//  program manager.hpp
//  Game Engine
//
//  Created by Indi Kernick on 9/2/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_3d_opengl_program_manager_hpp
#define engine_3d_opengl_program_manager_hpp

#ifdef USE_OPENGL

#include "program.hpp"
#include "constants.hpp"
#include <unordered_map>
#include "../program manager.hpp"
#include "set uniform.hpp"
#include "../../Resource/Handles/opengl texture.hpp"
#include "../../Application/global resource cache.hpp"
#include "../../Memory/view.hpp"

namespace Graphics3D {
  class ProgramManagerOpenGL : public ProgramManager {
  public:
    using Ptr = std::shared_ptr<ProgramManagerOpenGL>;
  
    ProgramManagerOpenGL();
    ~ProgramManagerOpenGL();
    
    void loadAll() override;
    void bind(ProgType) override;
    
    void setModel(const glm::mat4 &model) override;
    void setCamera(const glm::mat4 &view, const glm::mat4 &proj) override;
    void setMaterial(const Material &mat) override;
    void setLights(const std::vector<Scene::Light::AllProps> &lights,
                   const std::vector<glm::vec3> &lightsPos,
                   const std::vector<glm::vec3> &lightsDir) override;
    void setBones(const std::vector<glm::mat4> &bones) override;
    
    void setMaterial(const glm::vec4 &, const Res::ID &) override;
    
  private:
    std::unordered_map<ProgType, ProgramOpenGL> programs;
    ProgType bound;
    GLuint boundID = 0;
    glm::mat4 view, proj;
    
    GLuint whiteTex, blackTex;
    
    Res::TextureOpenGL::Ptr diffTex, ambiTex, specTex;
  };
}

#endif

#endif
