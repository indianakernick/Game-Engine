vec4 lighting(Material mat, Light light, Vertex vertex) {
  vec3 toLight = light.pos - vertex.pos;
  float lightDist = length(toLight);
  toLight = normalize(toLight);
  
  float diffCoef = max(0.0, dot(toLight, normal));
  float specCoef;
  if (mat.shininess == 0.0 || diffCoef == 0.0) {
    specCoef = 0.0;
  } else {
    specCoef = pow(
      max(0.0, dot(reflect(-toLight, normal), vertex.toCamera)),
      mat.shininess
    );
    //why doesn't this work
    //* sign(diffCoef)
    //* sign(shininess);
  }
  
  return vec4(
    (mat.diff * diffCoef * light.diff) +
    (mat.ambi * light.ambi) +
    (mat.spec * specCoef * light.spec),
    1.0
  );
}
