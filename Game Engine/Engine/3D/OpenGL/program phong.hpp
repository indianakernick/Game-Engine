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

namespace Graphics3D {
  namespace GLProgs {
    class Phong : public ProgramOpenGL {
    public:
      Phong(const char *name = "Phong",
            const char *vert = "texture.vert",
            const char *frag = "phong texture.frag");
    
      void load() override;
      
      void enableAll() override;
      void disableAll() override;
      
      void enableTexturePos();
      void disableTexturePos();
      
      void posPointer(size_t stride, size_t offset);
      void normalPointer(size_t stride, size_t offset);
      void texturePosPointer(size_t stride, size_t offset);
      
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
      
      GLint pos, normal, texturePos;
      
      const char *vert, *frag;
    };
  }
}

#endif

#endif
