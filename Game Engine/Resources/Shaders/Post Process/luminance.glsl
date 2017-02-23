vec4 process(sampler2D tex, vec2 pos) {
  const vec3 color = texture2D(tex, pos);
  return vec4(vec3((color.r * 0.299 + color.g * 0.587 + color.b * 0.114) / 3), 1);
}
