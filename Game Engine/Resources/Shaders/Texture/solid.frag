#version 410

uniform vec3 color;
uniform sampler2D colorTexture;
uniform bool hasColorTexture;

in vec2 fragTexturePos;

out vec4 outColor;

void main() {
  if (hasDiffuseTexture) {
    outColor = vec4(color * texture(diffuseTexture, fragTexturePos).rgb, 1.0);
  } else {
    outColor = vec4(color, 1.0);
  }
}
