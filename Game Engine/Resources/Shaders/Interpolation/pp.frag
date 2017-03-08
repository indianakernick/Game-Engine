#version 410

uniform sampler2D tex;

out vec4 outColor;

in vec2 texPos;

vec4 process(sampler2D, vec2);

void main() {
  outColor = process(tex, texPos);
}
