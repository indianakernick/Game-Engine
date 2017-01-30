#version 410

uniform mat4 model;
uniform mat4 transInvModel;
uniform mat4 mvp;

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texturePos;

out vec3 fragPos;
out vec3 fragNormal;
out vec2 fragTexturePos;

void main() {
  gl_Position = mvp * vec4(pos, 1.0);
  fragPos = (model * vec4(pos, 1.0)).xyz;
  fragNormal = normalize((transInvModel * vec4(normal, 0.0)).xyz);
  fragTexturePos = texturePos;
}
