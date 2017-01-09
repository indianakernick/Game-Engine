#version 410

const int MAX_LIGHTS = 16;
const float PI = 3.141592653589793;

uniform vec3 cameraDir;

uniform vec3 diffuse;
uniform vec3 ambient;
uniform vec3 specular;
uniform float shininess;
uniform sampler2D diffuseTexture;
uniform bool hasDiffuseTexture;

uniform float[MAX_LIGHTS] lightIntensity;
uniform vec3[MAX_LIGHTS] lightColor;
uniform vec3[MAX_LIGHTS] lightPos;
uniform int lightsNum;

in vec3 fragPos;
in vec3 fragNormal;
in vec2 fragTexturePos;

out vec4 outColor;

//light energy = light intensity * light color / distance ^ 2
//surface color = albedo * light energy * (surface normal . light direction)

void main() {
  outColor = vec4(0.0, 0.0, 0.0, 1.0);
  
  vec3 diffuseColor;
  if (hasDiffuseTexture) {
    diffuseColor = diffuse * texture(diffuseTexture, fragTexturePos).rgb;
  } else {
    diffuseColor = diffuse;
  }
  
  for (int i = 0; i < lightsNum; i++) {
    vec3 lightDir = lightPos[i] - fragPos;
    vec3 lightEnergy = (lightIntensity[i] * lightColor[i]) / dot(lightDir, lightDir);
    outColor += vec4(diffuse * lightEnergy * max(0.0, dot(fragNormal, normalize(lightDir))), 0.0);
    
    if (shininess != 0) {
      vec3 reflection = normalize(reflect(-lightDir, fragNormal));
      float cosReflectAngle = max(0.0, dot(cameraDir, reflection));
      outColor += vec4(specular * lightEnergy * pow(cosReflectAngle, shininess), 0.0);
    }
  }
  outColor += vec4(ambient * diffuse, 0.0);
}
