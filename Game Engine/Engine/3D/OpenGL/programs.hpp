//
//  programs.hpp
//  Game Engine
//
//  Created by Indi Kernick on 9/2/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_3d_opengl_programs_hpp
#define engine_3d_opengl_programs_hpp

#ifdef USE_OPENGL

#include "program.hpp"
#include "constants.hpp"
#include <unordered_map>
#include <vector>
#include "../material.hpp"
#include <glm/mat4x4.hpp>
#include "set uniform.hpp"
#include "../../Resource/Handles/opengl texture.hpp"
#include "../../Application/global resource cache.hpp"
#include "../Scene/light.hpp"
#include "../../Memory/buffer.hpp"
#include "../../Memory/view.hpp"
#include <array>
#include "../../Utils/combine.hpp"

template <>
struct std::hash<Graphics3D::ProgType> {
  size_t operator()(const Graphics3D::ProgType) const;
};

namespace Graphics3D {
  class ProgramsOpenGL {
  public:
    using Ptr = std::unique_ptr<ProgramsOpenGL>;
  
    ProgramsOpenGL();
    ~ProgramsOpenGL();
    
    void loadAll();
    void bind(ProgType);
    
    void setModel(const glm::mat4 &model);
    void setCamera(const glm::mat4 &view, const glm::mat4 &proj);
    void setMaterial(const Material &mat);
    void setLights(const std::vector<Scene::Light::AllProps> &lights,
                   const std::vector<glm::vec3> &lightsPos,
                   const std::vector<glm::vec3> &lightsDir);
    void setBones(const std::vector<glm::mat4> &bones);
    
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
