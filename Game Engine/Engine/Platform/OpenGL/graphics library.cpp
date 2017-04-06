//
//  graphics library.cpp
//  Game Engine
//
//  Created by Indi Kernick on 5/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "graphics library.hpp"

#ifdef USE_OPENGL

using namespace Graphics3D;

namespace {
  GLenum toGL(const TexWrap wrap) {
    switch (wrap) {
      case TexWrap::CLAMP:
        return GL_CLAMP;
      case TexWrap::CLAMP_BORDER:
        return GL_CLAMP_TO_BORDER;
      case TexWrap::REPEAT:
        return GL_REPEAT;
      case TexWrap::REPEAT_MIRROR:
        return GL_MIRRORED_REPEAT;
      default:
        assert(false);
    }
  }

  GLenum toGL(const TexMin min) {
    switch (min) {
      case TexMin::NEAREST:
        return GL_NEAREST;
      case TexMin::LINEAR:
        return GL_LINEAR;
      case TexMin::NEAREST_MIPMAP_NEAREST:
        return GL_NEAREST_MIPMAP_NEAREST;
      case TexMin::LINEAR_MIPMAP_NEAREST:
        return GL_LINEAR_MIPMAP_NEAREST;
      case TexMin::NEAREST_MIPMAP_LINEAR:
        return GL_NEAREST_MIPMAP_LINEAR;
      case TexMin::LINEAR_MIPMAP_LINEAR:
        return GL_LINEAR_MIPMAP_LINEAR;
      default:
        assert(false);
    }
  }

  GLenum toGL(const TexMag mag) {
    switch (mag) {
      case TexMag::NEAREST:
        return GL_NEAREST;
      case TexMag::LINEAR:
        return GL_LINEAR;
      default:
        assert(false);
    }
  }

  void setTexParams(const Graphics3D::TexParams params) {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, toGL(params.wrapS));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, toGL(params.wrapT));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, toGL(params.min));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, toGL(params.mag));
    if (params.wrapS == TexWrap::CLAMP_BORDER ||
        params.wrapT == TexWrap::CLAMP_BORDER) {
      glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, &params.border.r);
    }
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, params.af);
  }
  
  GLenum toGL(const Platform::Shader::Type type) {
    switch (type) {
      case Platform::Shader::Type::VERTEX:
        return GL_VERTEX_SHADER;
      case Platform::Shader::Type::FRAGMENT:
        return GL_FRAGMENT_SHADER;
      case Platform::Shader::Type::GEOMETRY:
        return GL_GEOMETRY_SHADER;
      default:
        assert(false);
    }
  }
  
  void compile(GLuint id) {
    glCompileShader(id);
    
    GLint status;
    glGetShaderiv(id, GL_COMPILE_STATUS, &status);
    if (status) {
      LOG_INFO(PLATFORM, "Successfully compiled shader");
    } else {
      LOG_ERROR(PLATFORM, "Failed to compile shader");
    }
    
    CHECK_OPENGL_ERROR();
  }
  
  void printInfoLog(GLuint id) {
    GLint logLength;
    glGetShaderiv(id, GL_INFO_LOG_LENGTH, &logLength);
    if (logLength) {
      std::unique_ptr<char[]> log(new char[logLength]);
      glGetShaderInfoLog(id, logLength, nullptr, log.get());
      LOG_INFO(PLATFORM, "Shader info log:\n%s", log.get());
    } else {
      LOG_INFO(PLATFORM, "Shader doesn't have an info log");
    }
    
    CHECK_OPENGL_ERROR();
  }
}

Platform::Texture::Ptr Platform::makeTexture(
  Memory::Buffer buf,
  glm::ivec2 size,
  const TexParams &params
) {
  assert(buf.size() == size.x * size.y * (3ull + params.hasAlpha));

  GLuint id;
  glGenTextures(1, &id);
  glBindTexture(GL_TEXTURE_2D, id);
  
  setTexParams(params);
  
  if (params.invert) {
    for (Byte *p = buf.begin(); p != buf.end(); p++) {
      *p = 255 - *p;
    }
  }
  
  if (params.hasAlpha) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB_ALPHA,
                 size.x, size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, buf.begin());
  } else {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB,
                 size.x, size.y, 0, GL_RGB, GL_UNSIGNED_BYTE, buf.begin());
  }
  
  glBindTexture(GL_TEXTURE_2D, 0);
  
  CHECK_OPENGL_ERROR();
  
  return std::make_shared<TextureImpl>(id);
}

Platform::Shader::Ptr Platform::makeShader(
  const Memory::Buffer buf,
  Shader::Type type
) {
  assert(buf.size());
  
  const GLuint id = glCreateShader(toGL(type));
  const GLchar *str = buf.cbegin<GLchar>();
  const GLint length = buf.size<GLint>();
  glShaderSource(id, 1, &str, &length);
  
  compile(id);
  printInfoLog(id);
  
  CHECK_OPENGL_ERROR();
  
  return std::make_shared<ShaderImpl>(type, id);
}

Platform::Shader::Ptr Platform::makeShader(
  const Memory::Buffer buf0,
  const Memory::Buffer buf1,
  Shader::Type type
) {
  assert(buf0.size());
  assert(buf1.size());
  
  const GLuint id = glCreateShader(toGL(type));
  const GLchar *strs[2] = {
    buf0.cbegin<GLchar>(),
    buf1.cbegin<GLchar>()
  };
  const GLint lengths[2] = {
    buf0.size<GLint>(),
    buf1.size<GLint>()
  };
  glShaderSource(id, 2, strs, lengths);
  
  compile(id);
  printInfoLog(id);
  
  CHECK_OPENGL_ERROR();
  
  return std::make_shared<ShaderImpl>(type, id);
}

#endif
