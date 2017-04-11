#version 410

uniform sampler2D tex;
uniform vec4 color;

in vec2 fragTexPos;

out vec4 outColor;

void main() {
  outColor = vec4(color.rgb, color.a * texture(tex, fragTexPos).r);
}
