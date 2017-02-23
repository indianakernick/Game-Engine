uniform vec4 color;

vec4 process(sampler2D tex, vec2 pos) {
  return texture2D(tex, pos) + color;
}
