vec4 process(sampler2D tex, vec2 pos) {
  return vec4(vec3(1) - texture2D(tex, pos).rgb, 1);
}
