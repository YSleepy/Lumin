#version 330 core
in vec2 vUV;
in vec3 vNormal;
in vec3 vFragPos;

struct Light{
    vec3 position;
    vec3 color;
};

out vec4 FragColor;

uniform sampler2D aTexture;
uniform Light aLight;

void main()
{
   vec3 norm = normalize(vNormal);
   vec3 lightDir = normalize(aLight.position - vFragPos);
   float diff = max(dot(norm, lightDir), 0.0);
   vec3 diffuse = diff * aLight.color;
   FragColor = texture(aTexture, vUV);
}
