#version 410

uniform ivec2 windowSize;

layout (location = 1) in vec2 pos;
layout (location = 3) in vec2 texPos;

out vec2 fragTexPos;

void main() {
  //pos is in pixels
  gl_Position.x = pos.x / windowSize.x * 2.0 - 1.0;
  gl_Position.y = (1.0 - pos.y / windowSize.y) * 2.0 - 1.0;
  gl_Position.z = 1.0;
  gl_Position.w = 1.0;
  
  fragTexPos = texPos;
}
