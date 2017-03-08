#version 410

const uint MAX_BONES_PER_VERTEX = 4;
const uint MAX_BONES = 128;

uniform mat4 mvp;
uniform mat4 model;
uniform mat4 transInvModel;
uniform mat4 bones[MAX_BONES];

layout (location = 0) in vec3 pos;
layout (location = 2) in vec3 normal;
layout (location = 3) in vec2 texturePos;
layout (location = 4) in uint boneID[MAX_BONES_PER_VERTEX];
layout (location = 8) in float boneWeight[MAX_BONES_PER_VERTEX];

out VertexData {
  vec3 pos;
  vec3 normal;
  vec2 texturePos;
} vertex;

void main() {
  //assumes that every vertex is attached to at least one bone.
  //this is usually the case
  mat4 boneTransform = bones[boneID[0]] * boneWeight[0];
  for (uint b = 1; b < MAX_BONES_PER_VERTEX; b++) {
    boneTransform += bones[boneID[b]] * boneWeight[b];
  }

  gl_Position = mvp * boneTransform * vec4(pos, 1.0);
  vertex.pos = (model * boneTransform * vec4(pos, 1.0)).xyz;
  vertex.normal = normalize((transInvModel * boneTransform * vec4(normal, 0.0)).xyz);
  vertex.texturePos = texturePos;
}
