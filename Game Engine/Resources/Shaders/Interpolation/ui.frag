#version 410

uniform sampler2D tex;
uniform vec4 color;

in vec2 fragTexPos;

out vec4 outColor;

void main() {
  vec4 texColor = texture(tex, fragTexPos);
  outColor.rgb = color.rgb * color.a + texColor.rgb * (1.0 - color.a);
  outColor.a = color.a;
}
