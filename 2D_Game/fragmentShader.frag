#version 330 core
in vec4 outColor;
in vec2 TexCoord;

out vec4 color;

//uniform vec4 outColor;
uniform sampler2D texture0; //GL_TEXTURE0

void main()
{
  //color = outColor;
  color = texture(texture0, TexCoord);
  //color = mix(texture(ourTexture1, TexCoord), texture(ourTexture2, TexCoord), 0.2);
}