#version 410

const uint MAX_LIGHTS = 16;
const uint LIGHT_DIRECT = 0;
const uint LIGHT_POINT = 1;
const uint LIGHT_SPOT = 2;

uniform vec3 cameraPos;

uniform vec3 diffuse;
uniform vec3 ambient;
uniform vec3 specular;
uniform float shininess;
uniform sampler2D diffuseTexture;
uniform sampler2D ambientTexture;
uniform sampler2D specularTexture;

uniform uint[MAX_LIGHTS] lightType;
uniform vec3[MAX_LIGHTS] lightDiff;
uniform vec3[MAX_LIGHTS] lightAmbi;
uniform vec3[MAX_LIGHTS] lightSpec;
uniform float[MAX_LIGHTS] lightIntensity;
uniform float[MAX_LIGHTS] lightAngle;
uniform vec3[MAX_LIGHTS] lightPos;
uniform vec3[MAX_LIGHTS] lightDir;
uniform uint lightsNum;

in vec3 fragPos;
in vec3 fragNormal;
in vec2 fragTexturePos;

out vec4 outColor;

//light energy = light intensity * light color / distance ^ 2
//surface color = albedo * light energy * (surface normal . light direction)

void lighting(int, vec3, vec3, vec3, vec3);

void directLight(int, vec3, vec3, vec3);
void pointLight(int, vec3, vec3, vec3);
void spotLight(int, vec3, vec3, vec3);

float lightAtten(float, vec3);

vec3 normal = normalize(fragNormal);

void main() {
  outColor = vec4(0.0, 0.0, 0.0, 1.0);
  vec3 diffuseColor = diffuse * texture(diffuseTexture, fragTexturePos).rgb;
  vec3 ambientColor = ambient * texture(ambientTexture, fragTexturePos).rgb;
  vec3 specularColor = specular * texture(specularTexture, fragTexturePos).rgb;
  
  for (int i = 0; i < lightsNum; i++) {
    switch (lightType[i]) {
      case LIGHT_DIRECT:
        directLight(i, diffuseColor, ambientColor, specularColor);
        break;
      case LIGHT_POINT:
        pointLight(i, diffuseColor, ambientColor, specularColor);
        break;
      case LIGHT_SPOT:
        spotLight(i, diffuseColor, ambientColor, specularColor);
    }
  }
  outColor.rgb = pow(outColor.rgb, vec3(1.0 / 2.2));
}

void directLight(int i, vec3 diffuseColor, vec3 ambientColor, vec3 specularColor) {
  lighting(i, diffuseColor, ambientColor, specularColor, vec3(1, 0, 0));
}

void pointLight(int i, vec3 diffuseColor, vec3 ambientColor, vec3 specularColor) {
  lighting(i, diffuseColor, ambientColor, specularColor, vec3(0, 0, 1));
}

void spotLight(int i, vec3 diffuseColor, vec3 ambientColor, vec3 specularColor) {
  if (acos(5) <= lightAngle[i]) {
  //if (acos(dot(normalize(fragPos - lightPos[i])), lightDir[i])) <= lightAngle[i]) {
    lighting(i, diffuseColor, ambientColor, specularColor, vec3(0, 0, 1));
  }
}

float lightAtten(float dist, vec3 attenCoef) {
  return 1/(attenCoef[0] + attenCoef[1] * dist + attenCoef[2] * dist * dist);
}
