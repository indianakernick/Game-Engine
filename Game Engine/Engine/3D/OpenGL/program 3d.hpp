//
//  program 3d.hpp
//  Game Engine
//
//  Created by Indi Kernick on 29/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_3d_opengl_program_3d_hpp
#define engine_3d_opengl_program_3d_hpp

#ifdef USE_OPENGL

#include "program.hpp"
#include <glm/gtc/type_ptr.hpp>
#include "../../Resource/Descriptions/opengl texture.hpp"
#include "../program 3d.hpp"

namespace Graphics3D {
  //i need a better name for this
  class ProgramOpenGL3D : public ProgramOpenGL,
                          public Program3D {
  public:
    ProgramOpenGL3D();
  
    void load() override;
    
    void enableAll() override;
    void disableAll() override;
    
    void enableTexturePos();
    void disableTexturePos();
    
    void posPointer(size_t stride, size_t offset);
    void normalPointer(size_t stride, size_t offset);
    void texturePosPointer(size_t stride, size_t offset);
    
    void setModel(const glm::mat4 &mat) override;
    void setView(const glm::mat4 &mat) override;
    void setProj(const glm::mat4 &mat) override;
    void setMat() override;
    
    void setMaterial(const Material &material) override;
    void setLights(const std::vector<LightProperties> &lights) override;
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
