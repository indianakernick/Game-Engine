#version 410

layout(location = 1) in vec2 pos;

out vec2 texPos;

void main() {
  gl_Position = vec4(pos, 0.0, 1.0);
  texPos = (pos + 1) * 0.5;
}
