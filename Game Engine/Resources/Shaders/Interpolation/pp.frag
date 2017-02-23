#version 410

uniform sampler2D tex;

out vec4 outColor;

vec4 process(sampler2D, vec2);

void main() {
  outColor = process(tex, gl_FragCoord.xy);
}
