#version 410

const uint MAX_HEIGHT = 1000;

layout (location = 0) in vec3 pos;
layout (location = 3) in vec2 texPos;

out vec2 fragTexPos;

void main() {
  gl_Position.x = pos.x * 2.0 - 1.0;
  gl_Position.y = (1.0 - pos.y) * 2.0 - 1.0;
  gl_Position.z = 1.0 - pos.z / MAX_HEIGHT;
  gl_Position.w = 1.0;
  
  fragTexPos = texPos;
}
