#pragma once
#include <GL/glew.h>
#include "GameEnums.h"
#include <SOIL/SOIL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext.hpp>

namespace GameWorld
{
	namespace WorldObjects
	{
		class WorldObject
		{
		private:
			virtual void SetupVAO(const GLuint positionAttribLocation, const GLuint colorAttribLocation, const GLuint textureAttribLocation) = 0;
		public:
			WorldObject() = default;
			virtual ~WorldObject() {};
			virtual GLuint GetVAO() const = 0;
			virtual void Draw() = 0;
			virtual WorldObjectType GetType() const = 0;
			virtual void DoMovement(const GLuint transformUniformLocation, const Movement movement, const GLfloat deltaTime) {};
		};
	}
}

