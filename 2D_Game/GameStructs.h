#pragma once
#include <GL/glew.h>
#include "Texture.h"

namespace GameWorld
{
	struct Vertex
	{
		GLfloat position[4];
		GLfloat color[4];
		GLfloat textureCoordinates[2];
	};
}