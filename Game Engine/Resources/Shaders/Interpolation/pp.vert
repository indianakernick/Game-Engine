#version 410

//texturePos location
layout(location = 2) in vec2 pos;

void main() {
  gl_Position.xy = pos;
}
