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
using namespace Platform;

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
  
  GLenum toGL(const Shader::Type type) {
    switch (type) {
      case Shader::Type::VERTEX:
        return GL_VERTEX_SHADER;
      case Shader::Type::FRAGMENT:
        return GL_FRAGMENT_SHADER;
      default:
        assert(false);
    }
  }
  
  template <typename ...ARGS>
  std::enable_if_t<allSameAs<Memory::Buffer, ARGS...>, void>
  uploadShaderSource(GLuint id, const ARGS ...bufs) {
    static_assert(sizeof...(ARGS));
    
    const GLchar *strs[sizeof...(ARGS)] = {
      bufs.template cdata<GLchar>()...
    };
    const GLint lengths[sizeof...(ARGS)] = {
      bufs.template size<GLint>()...
    };
    glShaderSource(id, static_cast<GLsizei>(sizeof...(ARGS)), strs, lengths);
    
    CHECK_OPENGL_ERROR();
  }
  
  void uploadShaderSource(GLuint id, const std::vector<Memory::Buffer> bufs) {
    assert(bufs.size());
    
    std::vector<const GLchar *> strs;
    strs.reserve(bufs.size());
    std::vector<GLint> lengths;
    lengths.reserve(bufs.size());
    
    for (auto b = bufs.cbegin(); b != bufs.cend(); ++b) {
      strs.push_back(b->cdata<GLchar>());
      lengths.push_back(b->size<GLint>());
    }
    
    glShaderSource(id, static_cast<GLsizei>(bufs.size()), strs.data(), lengths.data());
    
    CHECK_OPENGL_ERROR();
  }
  
  void compileShader(GLuint id) {
    glCompileShader(id);
    
    GLint status;
    glGetShaderiv(id, GL_COMPILE_STATUS, &status);
    if (!status) {
      throw ShaderLoadError("Failed to compile shader");
    }
    
    CHECK_OPENGL_ERROR();
  }
  
  void printShaderInfoLog(GLuint id) {
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
  
  GLuint attachShader(GLuint programID, const Shader::Ptr shader) {
    const ShaderImpl::Ptr impl = std::dynamic_pointer_cast<ShaderImpl>(shader);
    const GLuint shaderID = impl->getID();
    glAttachShader(programID, shaderID);
    
    CHECK_OPENGL_ERROR();
    
    return shaderID;
  }
  
  void linkProgram(GLuint id) {
    glLinkProgram(id);
    
    GLint status;
    glGetProgramiv(id, GL_LINK_STATUS, &status);
    if (!status) {
      throw ShaderProgramLoadError("Failed to link program");
    }
    
    CHECK_OPENGL_ERROR();
  }
  
  void printProgramInfoLog(GLuint id) {
    GLint length;
    glGetProgramiv(id, GL_INFO_LOG_LENGTH, &length);
    if (length) {
      std::unique_ptr<char[]> log(new char[length]);
      glGetProgramInfoLog(id, length, nullptr, log.get());
      LOG_INFO(PLATFORM, "Program info log:\n%s", log.get());
    } else {
      LOG_INFO(PLATFORM, "Program doesn't have an info log");
    }
    
    CHECK_OPENGL_ERROR();
  }
}

Texture::Ptr Platform::makeTexture(
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

Shader::Ptr Platform::makeShader(
  Shader::Type type,
  const Memory::Buffer buf
) {
  assert(buf.size());
  
  const GLuint id = glCreateShader(toGL(type));
  uploadShaderSource(id, buf);
  
  compileShader(id);
  printShaderInfoLog(id);
  
  CHECK_OPENGL_ERROR();
  
  return std::make_shared<ShaderImpl>(type, id);
}

Shader::Ptr Platform::makeShader(
  Shader::Type type,
  const Memory::Buffer buf0,
  const Memory::Buffer buf1
) {
  assert(buf0.size());
  assert(buf1.size());
  
  const GLuint id = glCreateShader(toGL(type));
  uploadShaderSource(id, buf0, buf1);
  
  compileShader(id);
  printShaderInfoLog(id);
  
  CHECK_OPENGL_ERROR();
  
  return std::make_shared<ShaderImpl>(type, id);
}

ShaderProgram::Ptr Platform::makeShaderProgram(
  const std::string &name,
  const std::vector<Shader::Ptr> &shaders) {
  assert(name.size());
  assert(shaders.size());
  
  LOG_DEBUG(PLATFORM, "Loading shader program \"%s\"", name.c_str());
  
  const GLuint programID = glCreateProgram();
  std::vector<GLuint> shaderIDs;
  shaderIDs.reserve(shaders.size());
  
  for (auto s = shaders.cbegin(); s != shaders.cend(); ++s) {
    shaderIDs.push_back(attachShader(programID, *s));
  }
  
  linkProgram(programID);
  
  for (auto s = shaderIDs.crbegin(); s != shaderIDs.crend(); ++s) {
    glDetachShader(programID, *s);
  }
  
  printProgramInfoLog(programID);
  
  CHECK_OPENGL_ERROR();
  
  return std::make_shared<ShaderProgramImpl>(name, programID);
}

#endif
