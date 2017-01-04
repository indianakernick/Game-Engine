//
//  program 3d.hpp
//  Game Engine
//
//  Created by Indi Kernick on 29/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_3d_opengl_program_3d_hpp
#define engine_3d_opengl_program_3d_hpp

#include "../../Application/opengl.hpp"

#ifdef __gl_h_

#include "program.hpp"
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "../material.hpp"
#include "../../Application/base.hpp"
#include "../../Resource/Descriptions/opengl texture.hpp"

namespace Graphics3D {
  class Program3D : public ProgramOpenGL {
  public:
    struct Light {
      float intensity = 0.0f;
      glm::vec3 color;
      glm::vec3 pos;
    };
  
    void load() override;
    
    void enableVertexArray() override;
    void disableVertexArray() override;
    
    void posPointer(size_t stride, size_t offset);
    void normalPointer(size_t stride, size_t offset);
    void texturePosPointer(size_t stride, size_t offset);
    
    void setModel(const glm::mat4 &mat);
    void setView(const glm::mat4 &mat);
    void setProj(const glm::mat4 &mat);
    void setMat();
    
    void setMaterial(const Material &material);
    void setLights(const std::vector<Light> &lights);
  private:
    glm::mat4 modelMat, viewMat, projMat;
    GLint model, transInvModel, mvp;
    
    GLint cameraDir;
    GLint diffuse, ambient, specular, shininess,
          diffuseTexture, hasDiffuseTexture;
    Resource::Handle::Ptr diffuseTextureHandle;
    
    GLint lightIntensity, lightColor, lightPos, lightsNum;
    
    GLint pos, normal, texturePos;
  };
};

#endif

#endif
