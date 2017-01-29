#version 410

const uint MAX_BONES_PER_VERTEX = 4;
const uint MAX_BONES = 128;

uniform mat4 model;
uniform mat4 transInvModel;
uniform mat4 mvp;
uniform mat4 bones[MAX_BONES];

in vec3 pos;
in vec3 normal;
in vec2 texturePos;
in uint boneID[MAX_BONES_PER_VERTEX];
in float boneWeight[MAX_BONES_PER_VERTEX];

out vec3 fragPos;
out vec3 fragNormal;
out vec2 fragTexturePos;

void main() {
  //assumes that every vertex is attached to at least one bone.
  //this is usually the case
  mat4 boneTransform = bones[boneID[0]] * boneWeight[0];
  for (uint b = 1; b < MAX_BONES_PER_VERTEX; b++) {
    boneTransform += bones[boneID[b]] * boneWeight[b];
  }

  gl_Position = mvp * boneTransform * vec4(pos, 1.0);
  fragPos = (model * boneTransform * vec4(pos, 1.0)).xyz;
  fragNormal = normalize((transInvModel * boneTransform * vec4(normal, 0.0)).xyz);
  fragTexturePos = texturePos;
}
