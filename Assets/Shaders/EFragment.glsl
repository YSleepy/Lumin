#version 330 core
in vec2 vUV;
in vec3 vNormal;

out vec4 FragColor;

uniform sampler2D aTexture;
void main()
{
//   vec4 texColor = texture(aTexture, vUV);
   FragColor = vec4(vNormal, 1.0);
}
