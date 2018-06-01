#include "Player.h"

namespace GameWorld
{
	namespace WorldObjects
	{
		void Player::InitializeVertices()
		{
			this->vertices[0] = { { -0.9f, -0.81f, +0.0f, +1.0f },{ +1.0f, +1.0f, +1.0f, +1.0f },{ +0.0f, +0.0f } };//lower left
			this->vertices[1] = { { -0.8f, -0.81f, +0.0f, +1.0f },{ +1.0f, +1.0f, +1.0f, +1.0f },{ +1.0f, +0.0f } };//lower right
			this->vertices[2] = { { -0.9f, -0.6f, +0.0f, +1.0f }, { +1.0f, +1.0f, +1.0f, +1.0f },{ +0.0f, +1.0f } };//upper left
			this->vertices[3] = { { -0.8f, -0.6f, +0.0f, +1.0f }, { +1.0f, +1.0f, +1.0f, +1.0f },{ +1.0f, +1.0f } };//upper right
		}

		Player::Player(const GLuint positionAttribLocation, const GLuint colorAttribLocation, const GLuint textureAttribLocation)
		{
			SetupVAO(positionAttribLocation, colorAttribLocation, textureAttribLocation);
		}


		Player::~Player()
		{
			// Properly de-allocate all resources once they've outlived their purpose
			glDeleteVertexArrays(1, &vao);
			glDeleteBuffers(1, &vbo);
		}

		void Player::SetupVAO(const GLuint positionAttribLocation, const GLuint colorAttribLocation, const GLuint textureAttribLocation)
		{
			InitializeVertices();

			SetupAnimations();

			glGenVertexArrays(1, &this->vao);
			glGenBuffers(1, &this->vbo);
			//glGenBuffers(1, &ebo);

			// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
			glBindVertexArray(this->vao);
			glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
			glBufferData(GL_ARRAY_BUFFER, sizeof(this->vertices), vertices, GL_STATIC_DRAW);
			glVertexAttribPointer(positionAttribLocation, 4, GL_FLOAT, GL_FALSE, sizeof(this->vertices[0]), (GLvoid*)0); //position
			glVertexAttribPointer(colorAttribLocation, 4, GL_FLOAT, GL_FALSE, sizeof(this->vertices[0]), (GLvoid*)(4 * sizeof(GLfloat))); //color
			glVertexAttribPointer(textureAttribLocation, 2, GL_FLOAT, GL_FALSE, sizeof(this->vertices[0]), (GLvoid*)(8 * sizeof(GLfloat))); //texture coordinates

			//Enable attributes
			glEnableVertexAttribArray(positionAttribLocation); //position
			glEnableVertexAttribArray(colorAttribLocation); //color
			glEnableVertexAttribArray(textureAttribLocation); //texture coordinates

			//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[0]);
			//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
			glBindVertexArray(0);

			this->positionAttribLocation = positionAttribLocation;//temp
			this->colorAttribLocation = colorAttribLocation;//temp
			this->textureCoordAttribLocation = textureAttribLocation;//temp
		}

		GLuint Player::GetVAO() const
		{
			return this->vao;
		}

		void Player::Draw()
		{
			// Bind Textures using texture units
			//glActiveTexture(GL_TEXTURE0);
			if (this->move == Movement::LEFT || this->previousMove == Movement::LEFT)
			{
				//glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, this->textureUnit);
			}
			else if(this->move == Movement::RIGHT || this->previousMove == Movement::RIGHT)
			{
				//glActiveTexture(GL_TEXTURE1);
				glBindTexture(GL_TEXTURE_2D, this->textureUnit2);
			}
			//glUniform1i(glGetUniformLocation(shaderProgram.Program, "ourTexture"), 0); //Assign a location value to the texture sampler.
																					   //Allows us to use multiple textures. Default value is zero so this isn't necessary

			glUniformMatrix4fv(this->transformUniformLocation, 1, GL_FALSE, glm::value_ptr(this->transform)); //Apply any transformations first
			glBindVertexArray(vao);
			glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
			glBindVertexArray(0);
			glActiveTexture(0);
			this->ChangeAnimationFrame();//temp

		}

		void Player::DoMovement(const GLuint transformUniformLocation, const Movement movement, const GLfloat deltaTime) //TO DO: What do I do with deltaTime???
		{
			GLfloat velocity = MOVEMENT_SPEED * deltaTime;
			this->transformUniformLocation = transformUniformLocation;

			if (movement == Movement::LEFT)
			{
				this->transform = glm::translate(this->transform, glm::vec3(-0.3f * velocity, 0.0f, 0.0f));
			}
			if (movement == Movement::RIGHT)
			{
				this->transform = glm::translate(this->transform, glm::vec3(0.3f * velocity, 0.0f, 0.0f));
			}
			if (movement == Movement::UP)
			{
				this->transform = glm::translate(this->transform, glm::vec3(0.0f, 0.3f * velocity, 0.0f));
			}
			if (movement == Movement::DOWN)
			{
				this->transform = glm::translate(this->transform, glm::vec3(0.0f, -0.3f * velocity, 0.0f));
			}

			if(this->move != movement)//temp
				this->move = movement;//temp
			/*if (movement == Movement::JUMP)
			{
				//MUST DRAW AND RENDER JUMP FRAMES HERE
				GLfloat maxOffset = +1.0f;
				GLfloat yOffset = +0.0f;
				while (yOffset < maxOffset)
				{
					this->transform = glm::translate(this->transform, glm::vec3(0.0f, 0.01, 0.0f));
					Draw();
				}

			}*/
			//std::cout << glm::to_string(this->transform) << std::endl << std::endl;
			//glUniformMatrix4fv(this->transformAttributeLocation, 1, GL_FALSE, glm::value_ptr(this->transform));
		}

		WorldObjectType Player::GetType() const
		{
			return WorldObjectType::PLAYER;
		}

		void Player::ChangeAnimationFrame()//temp logic
		{
			switch (this->move)
			{
			case Movement::LEFT:
				switch (this->frameIndex)
				{
				case 1:
					//lower left
					this->vertices[0].textureCoordinates[0] = 0.0f; //U
					this->vertices[0].textureCoordinates[1] = 0.4f; //70.0f;//V

					//lower right
					this->vertices[1].textureCoordinates[0] = (1.0f / 3.0f);//360.0f * (1.0f/3.0f); //U
					this->vertices[1].textureCoordinates[1] = 0.4f;//70.0f; //V

					//upper left
					this->vertices[2].textureCoordinates[0] = 0.0f; //U
					this->vertices[2].textureCoordinates[1] = 1.0f;//140.0f; //V

					//upper right
					this->vertices[3].textureCoordinates[0] = (1.0f / 3.0f);//360.0f * (1.0f / 3.0f); //U
					this->vertices[3].textureCoordinates[1] = 1.0f;//140.0f;//V
					this->frameIndex++;
					break;
				case 2:
					//lower left
					this->vertices[0].textureCoordinates[0] = (1.0f / 3.0f);//0.0f; //U
					this->vertices[0].textureCoordinates[1] = 0.4f; //70.0f;//V

					//lower right
					this->vertices[1].textureCoordinates[0] = (1.0f / 3.0f) * 2;//360.0f * (1.0f/3.0f); //U
					this->vertices[1].textureCoordinates[1] = 0.4f;//70.0f; //V

					//upper left
					this->vertices[2].textureCoordinates[0] = (1.0f / 3.0f);//0.0f; //U
					this->vertices[2].textureCoordinates[1] = 1.0f;//140.0f; //V

					//upper right
					this->vertices[3].textureCoordinates[0] = (1.0f / 3.0f) * 2;//360.0f * (1.0f / 3.0f); //U
					this->vertices[3].textureCoordinates[1] = 1.0f;//140.0f;//V
					this->frameIndex++;
					break;
				case 3:
					//lower left
					this->vertices[0].textureCoordinates[0] = (1.0f / 3.0f) * 2;//0.0f; //U
					this->vertices[0].textureCoordinates[1] = 0.4f; //70.0f;//V

					//lower right
					this->vertices[1].textureCoordinates[0] = (1.0f / 3.0f) * 3;//360.0f * (1.0f/3.0f); //U
					this->vertices[1].textureCoordinates[1] = 0.4f;//70.0f; //V

					//upper left
					this->vertices[2].textureCoordinates[0] = (1.0f / 3.0f) * 2;//0.0f; //U
					this->vertices[2].textureCoordinates[1] = 1.0f;//140.0f; //V

					//upper right
					this->vertices[3].textureCoordinates[0] = (1.0f / 3.0f) * 3;//360.0f * (1.0f / 3.0f); //U
					this->vertices[3].textureCoordinates[1] = 1.0f;//140.0f;//V
					this->frameIndex = 1;
					break;
				}
				this->previousMove = this->move;
				break;
			case Movement::RIGHT:
				switch (this->frameIndex)
				{
				case 1:
					//lower left
					this->vertices[0].textureCoordinates[0] = (1.0f / 3.0f) * 2;//0.0f; //U
					this->vertices[0].textureCoordinates[1] = 0.4f; //70.0f;//V

					//lower right
					this->vertices[1].textureCoordinates[0] = (1.0f / 3.0f) * 3;//360.0f * (1.0f/3.0f); //U
					this->vertices[1].textureCoordinates[1] = 0.4f;//70.0f; //V

					//upper left
					this->vertices[2].textureCoordinates[0] = (1.0f / 3.0f) * 2;//0.0f; //U
					this->vertices[2].textureCoordinates[1] = 1.0f;//140.0f; //V

					//upper right
					this->vertices[3].textureCoordinates[0] = (1.0f / 3.0f) * 3;//360.0f * (1.0f / 3.0f); //U
					this->vertices[3].textureCoordinates[1] = 1.0f;//140.0f;//V

					this->frameIndex++;
					break;
				case 2:
					//lower left
					this->vertices[0].textureCoordinates[0] = (1.0f / 3.0f);//0.0f; //U
					this->vertices[0].textureCoordinates[1] = 0.4f; //70.0f;//V

					//lower right
					this->vertices[1].textureCoordinates[0] = (1.0f / 3.0f) * 2;//360.0f * (1.0f/3.0f); //U
					this->vertices[1].textureCoordinates[1] = 0.4f;//70.0f; //V

					//upper left
					this->vertices[2].textureCoordinates[0] = (1.0f / 3.0f);//0.0f; //U
					this->vertices[2].textureCoordinates[1] = 1.0f;//140.0f; //V

					//upper right
					this->vertices[3].textureCoordinates[0] = (1.0f / 3.0f) * 2;//360.0f * (1.0f / 3.0f); //U
					this->vertices[3].textureCoordinates[1] = 1.0f;//140.0f;//V

					this->frameIndex++;
					break;
				case 3:
					//lower left
					this->vertices[0].textureCoordinates[0] = 0.0f; //U
					this->vertices[0].textureCoordinates[1] = 0.4f; //70.0f;//V

					//lower right
					this->vertices[1].textureCoordinates[0] = (1.0f / 3.0f);//360.0f * (1.0f/3.0f); //U
					this->vertices[1].textureCoordinates[1] = 0.4f;//70.0f; //V

					//upper left
					this->vertices[2].textureCoordinates[0] = 0.0f; //U
					this->vertices[2].textureCoordinates[1] = 1.0f;//140.0f; //V

					//upper right
					this->vertices[3].textureCoordinates[0] = (1.0f / 3.0f);//360.0f * (1.0f / 3.0f); //U
					this->vertices[3].textureCoordinates[1] = 1.0f;//140.0f;//V
					this->frameIndex = 1;
					break;
				}
				this->previousMove = this->move;
				break;
			default:
				//std::cout << "default case entered." << std::endl;
				if (this->previousMove == Movement::LEFT || this->previousMove == Movement::RIGHT)
				{
					this->move = this->previousMove;
					this->ChangeAnimationFrame(); //Look out! A recursive function call!!
				}
				break;
			}
			//Update VAO buffer data??
			glBindVertexArray(this->vao);
			glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
			glBufferData(GL_ARRAY_BUFFER, sizeof(this->vertices), vertices, GL_STATIC_DRAW);
			glVertexAttribPointer(this->positionAttribLocation, 4, GL_FLOAT, GL_FALSE, sizeof(this->vertices[0]), (GLvoid*)0); //position
			glVertexAttribPointer(this->colorAttribLocation, 4, GL_FLOAT, GL_FALSE, sizeof(this->vertices[0]), (GLvoid*)(4 * sizeof(GLfloat))); //color
			glVertexAttribPointer(this->textureCoordAttribLocation, 2, GL_FLOAT, GL_FALSE, sizeof(this->vertices[0]), (GLvoid*)(8 * sizeof(GLfloat))); //texture coordinates
			glBindVertexArray(0);

		}

		void Player::SetupAnimation(const Texture& texture, const AnimationType animationType)//temp logic
		{
		}

		void Player::SetupAnimations()//temp logic
		{
			this->move = Movement::RIGHT;
			this->previousMove = Movement::RIGHT;

			Texture batLeftTexture("battoleft.png");// are both of these textures sharing GLTEXTURE0??? Seems like it.
			Texture batRightTexture("battoright.png");

			this->textureUnit = batLeftTexture.GetIndex();
			this->textureUnit2 = batRightTexture.GetIndex();
			this->frameIndex = 1;
		}
	}
}