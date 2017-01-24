#version 410

const uint MAX_BONES_PER_VERTEX = 4;
const uint MAX_BONES = 128;

uniform mat4 model;
uniform mat4 transInvModel;
uniform mat4 mvp;
uniform mat4 bones[MAX_BONES];
uniform uint numBones;

in vec3 pos;
in vec3 normal;
in vec2 texturePos;
in uint boneID[MAX_BONES_PER_VERTEX];
in float boneWeight[MAX_BONES_PER_VERTEX];

out vec3 fragPos;
out vec3 fragNormal;
out vec2 fragTexturePos;

void main() {
  mat4 boneTransform;
  if (boneWeight[0] == 0.0) {
    boneTransform = mat4(1.0);
  } else {
    boneTransform = mat4(0.0);
    for (uint i = 0; i < MAX_BONES_PER_VERTEX; i++) {
      boneTransform += bones[boneID] * boneWeight[i];
    }
  }

  gl_Position = mvp * boneTransform * vec4(pos, 1.0);
  fragPos = (model * boneTransform * vec4(pos, 1.0)).xyz;
  fragNormal = normalize((transInvModel * boneTransform * vec4(normal, 0.0)).xyz);
  fragTexturePos = texturePos;
}
