#version 410

const int MAX_LIGHTS = 16;
const float PI = 3.141592653589793;
const int LIGHT_DIRECT = 0;
const int LIGHT_SPHERE = 1;
const int LIGHT_CIRC_SPOT = 2;
const int LIGHT_RECT_SPOT = 3;

uniform vec3 cameraPos;

uniform vec3 diffuse;
uniform vec3 ambient;
uniform vec3 specular;
uniform float shininess;
uniform sampler2D diffuseTexture;
uniform bool hasDiffuseTexture;

uniform int[MAX_LIGHTS] lightType;
uniform vec3[MAX_LIGHTS] lightColor;
uniform float[MAX_LIGHTS] lightIntensity;
uniform float[MAX_LIGHTS] lightHoriAngle;
uniform float[MAX_LIGHTS] lightVertAngle;
uniform vec3[MAX_LIGHTS] lightPos;
uniform vec3[MAX_LIGHTS] lightDir;
uniform int lightsNum;

in vec3 fragPos;
in vec3 fragNormal;
in vec2 fragTexturePos;

out vec4 outColor;

//light energy = light intensity * light color / distance ^ 2
//surface color = albedo * light energy * (surface normal . light direction)

vec4 directionalLight(int, vec3);
vec4 sphericalLight(int, vec3);
vec4 circularSpotLight(int, vec3);
vec4 rectangularSpotLight(int, vec3);

void main() {
  outColor = vec4(0.0, 0.0, 0.0, 1.0);
  vec3 diffuseColor;
  if (hasDiffuseTexture) {
    diffuseColor = diffuse * texture(diffuseTexture, fragTexturePos).rgb;
  } else {
    diffuseColor = diffuse;
  }
  
  for (int i = 0; i < lightsNum; i++) {
    switch (lightType[i]) {
      case LIGHT_DIRECT:
        outColor += directionalLight(i, diffuseColor);
        break;
      case LIGHT_SPHERE:
        outColor += sphericalLight(i, diffuseColor);
        break;
      case LIGHT_CIRC_SPOT:
        outColor += circularSpotLight(i, diffuseColor);
        break;
      case LIGHT_RECT_SPOT:
        outColor += rectangularSpotLight(i, diffuseColor);
    }
  }
  outColor += vec4(ambient * diffuseColor, 0.0);
}

vec4 directionalLight(int i, vec3 diffuseColor) {
  return vec4(lightDir[i], 0.0);
}

vec4 sphericalLight(int i, vec3 diffuseColor) {
  vec3 toLight = lightPos[i] - fragPos;
  vec3 toCamera = normalize(cameraPos - fragPos);
  vec3 lightEnergy = (lightIntensity[i] * lightColor[i]) / dot(toLight, toLight);
  vec4 outColor = vec4(diffuseColor * lightEnergy * max(0.0, dot(fragNormal, normalize(toLight))), 0.0);
  
  if (shininess != 0.0) {
    vec3 reflection = normalize(reflect(-toLight, fragNormal));
    float cosReflectAngle = max(0.0, dot(toCamera, reflection));
    outColor += vec4(specular * lightEnergy * pow(cosReflectAngle, shininess), 0.0);
  }
  return outColor;
}

vec4 circularSpotLight(int i, vec3 diffuseColor) {
  return vec4(lightHoriAngle[i], 0.0, 0.0, 0.0);
}

vec4 rectangularSpotLight(int i, vec3 diffuseColor) {
  return vec4(lightHoriAngle[i], lightVertAngle[i], 0.0, 0.0);
}
