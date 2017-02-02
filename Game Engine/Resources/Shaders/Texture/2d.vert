#version 410

uniform mat3 mvp;

layout (location = 0) in vec2 pos;
layout (location = 3) in vec2 texturePos;

out vec2 fragTexturePos;

void main() {
  gl_Position = vec4(mvp * vec3(pos, 1.0), 1.0);
  fragTexturePos = texturePos;
}
