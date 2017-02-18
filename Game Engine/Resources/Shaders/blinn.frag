#version 410

const uint MAX_LIGHTS = 16;

uniform vec3 cameraPos;

uniform float shininess;

uniform uint[MAX_LIGHTS] lightType;
uniform vec3[MAX_LIGHTS] lightDiff;
uniform vec3[MAX_LIGHTS] lightAmbi;
uniform vec3[MAX_LIGHTS] lightSpec;
uniform float[MAX_LIGHTS] lightIntensity;
uniform float[MAX_LIGHTS] lightAngle;
uniform vec3[MAX_LIGHTS] lightPos;
uniform vec3[MAX_LIGHTS] lightDir;

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
  float specCoef = pow(
    max(0.0, dot(normalize(toLight + toCamera), normal)),
    shininess
  ) * sign(shininess) * sign(diffCoef);
  
  vec3 lightDiffIntensity = lightDiff[i] * lightIntensity[i] * lightAtten(lightDist, atten);
  vec3 lightSpecIntensity = lightSpec[i] * lightIntensity[i] * lightAtten(lightDist, atten);
  
  outColor.rgb +=
    (diffuseColor * diffCoef * lightDiffIntensity) +
    (ambientColor * lightAmbi[i]) +
    (specularColor * specCoef * lightSpecIntensity);
}
