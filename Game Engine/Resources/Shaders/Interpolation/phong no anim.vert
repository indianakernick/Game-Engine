#version 410

uniform mat4 mvp;
uniform mat4 model;
uniform mat4 transInvModel;

layout (location = 0) in vec3 pos;
layout (location = 2) in vec3 normal;
layout (location = 3) in vec2 texturePos;

out VertexData {
  vec3 pos;
  vec3 normal;
  vec2 texturePos;
} vertex;

void main() {
  gl_Position = mvp * vec4(pos, 1.0);
  vertex.pos = (model * vec4(pos, 1.0)).xyz;
  vertex.normal = normalize((transInvModel * vec4(normal, 0.0)).xyz);
  vertex.texturePos = texturePos;
}
