#pragma once
#include <iostream>
#include "GameStructs.h"
#include "GameEnums.h"
#include "Animation.h"
#include "WorldObject.h"
#include "Texture.h"
#include <vector>
#include <unordered_map>

namespace GameWorld
{
	namespace WorldObjects
	{
		class Player : public WorldObject
		{
		private:
			GLuint vao;
			GLuint vbo;
			GLuint ebo;
			const GLfloat MOVEMENT_SPEED = 3.0f;
			glm::mat4 transform;
			GLuint transformUniformLocation;
			Vertex vertices[4];
			bool isGrounded;
			glm::vec3 groundLevel;
			std::unordered_map<AnimationType, Animation> animations;

			GLint textureUnit;//temp
			GLint textureUnit2;
			GLint frameIndex;//temp
			//Texture texture;//temp
			GLuint positionAttribLocation; //temp
			GLuint colorAttribLocation;//temp
			GLuint textureCoordAttribLocation;//temp
			Movement move;//temp
			Movement previousMove;//temp

			void SetupAnimation(const Texture & texture, const AnimationType animationType);//temp
			void SetupAnimations();//temp

			void InitializeVertices();
			void SetupVAO(const GLuint positionAttribLocation, const GLuint colorAttribLocation, const GLuint textureAttribLocation) override;
		public:
			Player(const GLuint positionAttribLocation, const GLuint colorAttribLocation, const GLuint textureAttribLocation);
			~Player();
			virtual GLuint GetVAO() const override;
			void Draw() override;
			void DoMovement(const GLuint transformUniformLocation, const Movement movement, const GLfloat deltaTime) override;
			WorldObjectType GetType() const override;
			bool IsGrounded() const { return this->isGrounded; }
			void ChangeAnimationFrame();//temp
		};
	}
}
