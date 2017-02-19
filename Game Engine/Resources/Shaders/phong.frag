#version 410

const uint MAX_LIGHTS = 16;

uniform vec3 cameraPos;

uniform float shininess;

uniform vec3[MAX_LIGHTS] lightDiff;
uniform vec3[MAX_LIGHTS] lightAmbi;
uniform vec3[MAX_LIGHTS] lightSpec;
uniform float[MAX_LIGHTS] lightIntensity;
uniform vec3[MAX_LIGHTS] lightPos;

in vec3 fragPos;

out vec4 outColor;

float lightAtten(float, vec3);

vec3 normal;

void lighting(int i, vec3 diffuseColor, vec3 ambientColor, vec3 specularColor, vec3 atten) {
  vec3 toLight = lightPos[i] - fragPos;
  float lightDist = length(toLight);
  toLight = normalize(toLight);
  vec3 toCamera = normalize(cameraPos - fragPos);
  
  float diffCoef = max(0.0, dot(toLight, normal));
  float specCoef;
  if (shininess == 0 || diffCoef == 0) {
    specCoef = 0;
  } else {
    specCoef = pow(
      max(0.0, dot(reflect(-toLight, normal), toCamera)),
      shininess
    );
    //why doesn't this work
    //* sign(diffCoef)
    //* sign(shininess);
  }
  
  vec3 lightDiffIntensity = lightDiff[i] * lightIntensity[i] * lightAtten(lightDist, atten);
  vec3 lightSpecIntensity = lightSpec[i] * lightIntensity[i] * lightAtten(lightDist, atten);
  
  outColor.rgb +=
    (diffuseColor * diffCoef * lightDiffIntensity) +
    (ambientColor * lightAmbi[i]) +
    (specularColor * specCoef * lightSpecIntensity);
}
