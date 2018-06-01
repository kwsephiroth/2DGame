#version 330 core
layout (location = 0) in vec4 position;
layout (location = 1) in vec4 color;
layout (location = 2) in vec2 texCoord;

out vec4 outColor;
out vec2 TexCoord;

uniform mat4 transform;
uniform mat4 previousTransform;

void main()
{
	vec4 transformedPosition = transform * position;

	//Define screen bounds
	/*if(transformedPosition.x > 1.0f)
	{

	}
	if(transformedPosition.x < -1.0f)
	{

	}
	if(transformedPosition.y > 1.0f)
	{

	}
	if(transformedPosition.y < -1.0f)
	{

	}*/

	gl_Position = transformedPosition;

	outColor = color;
    TexCoord = vec2(texCoord.x, 1.0 - texCoord.y);
}