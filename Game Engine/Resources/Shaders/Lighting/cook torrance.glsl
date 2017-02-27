vec4 lighting(Material mat, Light light, Vertex vertex) {
  vec3 toLight = light.pos - vertex.pos;
  float lightDist = length(toLight);
  toLight = normalize(toLight);
  
  float diffCoef = max(0.0, dot(toLight, normal));
  float specCoef;
  if (mat.shininess == 0.0 || diffCoef == 0.0) {
    specCoef = 0.0;
  } else {
    //I think these are surposed to be calculated from some
    //other parameters like index of refraction or something.
    float f0 = 0.1;
    float m = mat.shininess;
  
    vec3 h = normalize(toLight + vertex.toCamera);
    vec3 n = vertex.normal;
    vec3 l = toLight;
    vec3 v = vertex.toCamera;
    
    float nl = dot(n, l);
    float nv = dot(n, v);
    float nh = dot(n, h);
    float vh = dot(v, h);
    
    float f = f0 + pow(1.0 - vh, 5.0) * (1.0 - f0);
    float d = 1 / (m*m * pow(nh, 4.0)) * exp((nh * nh - 1.0) / (m*m * nh*nh));
    float g = min(1.0, min((2.0 * nv * nh) / vh, (2.0 * nl * nh) / vh));
    
    specCoef = (f * d * g) / (4.0 * nv * nl);
  }
  
  return vec4(
    (mat.diff * diffCoef * light.diff) +
    (mat.ambi * light.ambi) +
    (mat.spec * specCoef * light.spec),
    1.0
  );
}
