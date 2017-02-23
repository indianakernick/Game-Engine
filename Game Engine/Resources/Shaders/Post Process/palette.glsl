uniform float resolution;

vec4 process(sampler2D tex, vec2 pos) {
  return round(texture2D(tex, pos) * resolution) / resolution;
}
