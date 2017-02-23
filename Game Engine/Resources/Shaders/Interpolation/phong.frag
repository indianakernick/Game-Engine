#version 410

const uint MAX_LIGHTS = 16;
const uint LIGHT_DIRECT = 0;
const uint LIGHT_POINT = 1;
const uint LIGHT_SPOT = 2;

uniform vec3 cameraPos;

uniform vec3 diff;
uniform vec3 ambi;
uniform vec3 spec;
uniform sampler2D diffTex;
uniform sampler2D ambiTex;
uniform sampler2D specTex;
uniform float shininess;

uniform uint[MAX_LIGHTS] lightType;
uniform vec3[MAX_LIGHTS] lightPos;
uniform vec3[MAX_LIGHTS] lightDir;
uniform vec3[MAX_LIGHTS] lightDiff;
uniform vec3[MAX_LIGHTS] lightAmbi;
uniform vec3[MAX_LIGHTS] lightSpec;
uniform float[MAX_LIGHTS] lightIntensity;
uniform float[MAX_LIGHTS] lightInnerAngle;
uniform float[MAX_LIGHTS] lightOuterAngle;
uniform uint lightsNum;

in VertexData {
  vec3 pos;
  vec3 normal;
  vec2 texturePos;
} vertex;

out vec4 outColor;

vec4 mixLights(vec3, vec3, vec2);

vec3 normal = normalize(vertex.normal);

void main() {
  outColor = mixLights(vertex.pos, normal, vertex.texturePos);
  outColor.rgb = pow(outColor.rgb, vec3(1.0 / 2.2));
}

struct Material {
  vec3 diff;
  vec3 ambi;
  vec3 spec;
  float shininess;
};

struct Light {
  vec3 pos;
  vec3 diff;
  vec3 ambi;
  vec3 spec;
};

struct Vertex {
  vec3 pos;
  vec3 normal;
  vec3 toCamera;
};

vec4 lighting(Material, Light, Vertex);

float lightAtten(float dist, vec3 attenCoef) {
  return 1.0 / (attenCoef[0] + attenCoef[1] * dist + attenCoef[2] * dist * dist);
}

vec4 directLight(int i, Material mat, Light light, Vertex vertex) {
  float intensity =
    lightIntensity[i] *
    lightAtten(length(light.pos - vertex.pos), vec3(1, 0, 0));
  light.diff *= intensity;
  light.spec *= intensity;
  
  return lighting(mat, light, vertex);
}

vec4 pointLight(int i, Material mat, Light light, Vertex vertex) {
  float intensity =
    lightIntensity[i] *
    lightAtten(length(light.pos - vertex.pos), vec3(1, 0, 1));
  light.diff *= intensity;
  light.spec *= intensity;
  
  return lighting(mat, light, vertex);
}

vec4 spotLight(int i, Material mat, Light light, Vertex vertex) {
  vec3 lightToFrag = normalize(vertex.pos - light.pos);
  float angle = acos(dot(lightToFrag, lightDir[i]));
  if (angle <= lightOuterAngle[i]) {
    //intensityCoef will be 0 if its at outerAngle and 1 if its at innerAngle
    //innerAngle and outerAngle aren't in the Light struct because the lighting
    //calculation doesn't need to know about the type of light it is dealing
    //with
    float intensity =
      lightIntensity[i] *
      lightAtten(length(light.pos - vertex.pos), vec3(1, 0, 1)) *
      (angle - lightOuterAngle[i]) /
      (lightInnerAngle[i] - lightOuterAngle[i]);
    light.diff *= intensity;
    light.spec *= intensity;
    
    return lighting(mat, light, vertex);
  } else {
    return vec4(0.0);
  }
}

vec4 mixLights(vec3 pos, vec3 normal, vec2 texPos) {
  vec4 color = vec4(0.0);
  
  Material mat;
  mat.diff = diff * texture(diffTex, texPos).rgb;
  mat.ambi = ambi * texture(ambiTex, texPos).rgb;
  mat.spec = spec * texture(specTex, texPos).rgb;
  mat.shininess = shininess;
  
  Vertex vertex;
  vertex.pos = pos;
  vertex.normal = normal;
  vertex.toCamera = normalize(cameraPos - pos);
  
  for (int i = 0; i < lightsNum; i++) {
    Light light;
    light.pos = lightPos[i];
    light.diff = lightDiff[i];
    light.ambi = lightAmbi[i];
    light.spec = lightSpec[i];
  
    switch (lightType[i]) {
      case LIGHT_DIRECT:
        color += directLight(i, mat, light, vertex);
        break;
      case LIGHT_POINT:
        color += pointLight(i, mat, light, vertex);
        break;
      case LIGHT_SPOT:
        color += spotLight(i, mat, light, vertex);
    }
  }
  
  return color;
}
