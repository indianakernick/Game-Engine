#version 410

uniform sampler2D tex;
uniform vec4 color;

in vec2 fragTexPos;

out vec4 outColor;

//Still here in case I need it later
vec4 blend(vec4 back, vec4 fore) {
  return vec4(
    fore.rgb * fore.a + back.rgb * (1.0 - fore.a),
    fore.a + back.a * (1.0 - fore.a)
  );
}

void main() {
  vec4 texColor = texture(tex, fragTexPos);
  outColor = color * texColor;
}
