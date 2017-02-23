const float SIZE = 3;

uniform float kernel[SIZE * SIZE];
uniform float divisor;
uniform float offset;

vec4 process(sampler2D tex, vec2 pos) {
  vec3 sum = vec3(0);
  const vec2 size = vec2(textureSize(tex, 0));
  vec2 kPos = vec2(0, 0);
  for (; kPos.y < SIZE; kPos.y++) {
    for (; kPos.x < SIZE; kPos.x++) {
      sum += texture2D(tex, vec2(pos + (kPos - (SIZE - 1) / 2)) / size).rgb
             * kernel[kPos.y * SIZE + kPos.x];
    }
  }
  
  return vec4(sum / divisor + offset, 1);
}
