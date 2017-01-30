//
//  program phong.hpp
//  Game Engine
//
//  Created by Indi Kernick on 29/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_3d_opengl_program_phong_hpp
#define engine_3d_opengl_program_phong_hpp

#ifdef USE_OPENGL

#include "program.hpp"
#include <glm/gtc/type_ptr.hpp>
#include "../../Resource/Handles/opengl texture.hpp"
#include <vector>
#include "../material.hpp"
#include "../Scene/light.hpp"
#include "set uniform.hpp"
#include "attribs.hpp"

namespace Graphics3D {
  class Phong : public ProgramOpenGL {
  public:
    Phong(const char *name = "Phong",
          const char *vert = "phong texture.vert",
          const char *frag = "phong texture.frag");
  
    void load() override;
    
    void enableAll() override;
    void disableAll() override;
    
    void enableTexturePos();
    void disableTexturePos();
    
    void setModel(const glm::mat4 &mat);
    void setView(const glm::mat4 &mat);
    void setProj(const glm::mat4 &mat);
    void setMat();
    
    void setMaterial(const Material &material);
    void setLights(const std::vector<Scene::Light::AllProps> &lights,
                   const std::vector<glm::vec3> &lightsPos,
                   const std::vector<glm::vec3> &lightsDir);
  private:
    glm::mat4 modelMat, viewMat, projMat;
    GLint model, transInvModel, mvp;
    
    GLint cameraPos;
    GLint diffuse, ambient, specular, shininess,
          diffuseTexture, hasDiffuseTexture;
    Res::TextureOpenGL::Ptr diffuseTextureHandle;
    
    GLint lightType, lightColor, lightIntensity, lightHoriAngle,
          lightVertAngle, lightPos, lightDir, lightsNum;
    
    const char *vert, *frag;
  };
}

#endif

#endif
