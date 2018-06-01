#pragma once
#include "GameStructs.h"
#include "WorldObject.h"
#include "Texture.h"
#include <memory>

namespace GameWorld
{
	namespace WorldObjects
	{
		class Ground : public WorldObject
		{
		private:
			GLuint vao;
			GLuint vbo;
			GLuint ebo;
			glm::vec3 groundLevel;
			void InitializeVertices();
			Vertex vertices[4];
			void SetupVAO(const GLuint positionAttribLocation, const GLuint colorAttribLocation, const GLuint textureAttribLocation) override;
			std::unique_ptr<Texture> texture;
		public:
			Ground(const GLuint positionAttribLocation, const GLuint colorAttribLocation, const GLuint textureAttribLocation);
			~Ground();
			GLuint GetVAO() const override;
			void Draw() override;
			WorldObjectType GetType() const override;
			const glm::vec3 & GetGroundLevel();
		};
	}
}

