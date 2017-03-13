#version 410

uniform sampler2D tex;
uniform vec4 color;

in vec2 fragTexPos;

out vec4 outColor;

vec4 blend(vec4 back, vec4 fore) {
  vec4 ret;
  ret.rgb = fore.rgb * fore.a + back.rgb * (1.0 - fore.a);
  ret.a = fore.a + back.a * (1.0 - fore.a);
  return ret;
}

void main() {
  vec4 texColor = texture(tex, fragTexPos);
  outColor = blend(color, texColor);
}
