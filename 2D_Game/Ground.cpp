#include "Ground.h"

namespace GameWorld
{
	namespace WorldObjects
	{
		void Ground::InitializeVertices()
		{
			this->vertices[0] = { { -1.0f, -0.8f, +0.0f, +1.0f },{ +0.5f, +0.5f, +0.5f, +1.0f },{ +0.0f, +0.0f } };
			this->vertices[1] = { { 1.0f, -0.8f, +0.0f, +1.0f },{ +0.5f, +0.5f, +0.5f, +1.0f },{ +1.0f, +0.0f } };
			this->vertices[2] = { { -1.0f, -1.0f, +0.0f, +1.0f },{ +0.5f, +0.5f, +0.5f, +1.0f },{ +0.0f, +1.0f } };
			this->vertices[3] = { { 1.0f, -1.0f, +0.0f, +1.0f },{ +0.5f, +0.5f, +0.5f, +1.0f },{ +1.0f, +1.0f } };

			this->groundLevel = glm::vec3(0.0f, -0.8f, 0.0f); //Set to highest Y-axis value
		}

		void Ground::SetupVAO(const GLuint positionAttribLocation, const GLuint colorAttribLocation, const GLuint textureAttribLocation)
		{
			InitializeVertices();
			glGenVertexArrays(1, &this->vao);
			glGenBuffers(1, &this->vbo);
			//glGenBuffers(1, &ebo);

			// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
			glBindVertexArray(this->vao);
				glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
				glBufferData(GL_ARRAY_BUFFER, sizeof(this->vertices), this->vertices, GL_STATIC_DRAW);
				glVertexAttribPointer(positionAttribLocation, 4, GL_FLOAT, GL_FALSE, sizeof(this->vertices[0]), (GLvoid*)0); //position
				glVertexAttribPointer(colorAttribLocation, 4, GL_FLOAT, GL_FALSE, sizeof(this->vertices[0]), (GLvoid*)(4 * sizeof(GLfloat))); //color
				glVertexAttribPointer(textureAttribLocation, 2, GL_FLOAT, GL_FALSE, sizeof(this->vertices[0]), (GLvoid*)(8 * sizeof(GLfloat))); //texture coordinates
				glEnableVertexAttribArray(positionAttribLocation); //position
				glEnableVertexAttribArray(colorAttribLocation); //color
				glEnableVertexAttribArray(textureAttribLocation); //texture coordinates
			glBindVertexArray(0);
		}

		Ground::Ground(const GLuint positionAttribLocation, const GLuint colorAttribLocation, const GLuint textureAttribLocation)
		{
			SetupVAO(positionAttribLocation, colorAttribLocation, textureAttribLocation);
		}

		Ground::~Ground()
		{
			glDeleteVertexArrays(1, &this->vao);
			glDeleteBuffers(1, &this->vbo);
		}

		GLuint Ground::GetVAO() const
		{
			return this->vao;
		}

		void Ground::Draw()
		{
			glBindVertexArray(this->vao);
			glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
			glBindVertexArray(0);
		}

		WorldObjectType Ground::GetType() const
		{
			return WorldObjectType::GROUND;
		}

		const glm::vec3 & Ground::GetGroundLevel()
		{
			return this->groundLevel;
		}
	}
}
