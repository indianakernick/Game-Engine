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

vec4 directLight(int, vec3);
vec4 pointLight(int, vec3);
vec4 spotLight(int, vec3);

void main() {
  outColor = vec4(0.0, 0.0, 0.0, 1.0);
  vec3 diffuseColor = diffuse * texture(diffuseTexture, fragTexturePos).rgb;
  
  for (int i = 0; i < lightsNum; i++) {
    switch (lightType[i]) {
      case LIGHT_DIRECT:
        outColor += directLight(i, diffuseColor);
        break;
      case LIGHT_POINT:
        outColor += pointLight(i, diffuseColor);
        break;
      case LIGHT_SPOT:
        outColor += spotLight(i, diffuseColor);
    }
  }
  outColor += vec4(ambient * diffuseColor, 0.0);
}

vec4 directLight(int i, vec3 diffuseColor) {
  return vec4(lightDir[i], 0.0);
}

vec4 pointLight(int i, vec3 diffuseColor) {
  vec3 toLight = lightPos[i] - fragPos;
  vec3 toCamera = normalize(cameraPos - fragPos);
  vec3 lightEnergy = (lightIntensity[i] * lightDiff[i]) / dot(toLight, toLight);
  vec4 outColor = vec4(diffuseColor * lightEnergy * max(0.0, dot(fragNormal, normalize(toLight))), 0.0);
  
  if (shininess != 0.0) {
    vec3 reflection = normalize(reflect(-toLight, fragNormal));
    float cosReflectAngle = max(0.0, dot(toCamera, reflection));
    outColor += vec4(specular * lightEnergy * pow(cosReflectAngle, shininess), 0.0);
  }
  return outColor;
}

vec4 spotLight(int i, vec3 diffuseColor) {
  /*
  if (acos(dot(normalize(-toLight), lightDir[i])) > lightAngle[i]) {
    continue;
  }
  */
  return vec4(lightAngle[i], 0.0, 0.0, 0.0);
}
