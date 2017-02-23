vec4 process(sampler2D tex, vec2 pos) {
  return vec4(vec3(dot(texture2D(tex, pos).rgb, vec3(1)) / 3), 1);
}
