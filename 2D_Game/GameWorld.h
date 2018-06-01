#pragma once
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
//#include <memory>
//#include <string>
#include <vector>
#include "GameStructs.h"
#include "GameEnums.h"
#include "WorldObject.h"
#include "Player.h"
#include "Ground.h"

namespace GameWorld
{
	using namespace WorldObjects;

	class World
	{
	private:
		GLint width;
		GLint height;
		std::string name;
		GLFWwindow* window;
		std::string vertexShaderPath;
		std::string fragmentShaderPath;
		Shader* shaderProgram;
		std::vector<WorldObject*> worldObjects;//TODO: Switch to vector of smart pointers
		void InitializeGameWindow();
		void InitializeShaderProgram();
		//void InitializeShaderProgram(const GLchar* vertexShaderPath, const GLchar* fragmentShaderPath);
		void InitializeGlew();
		void InitializeWorldObjects();
		void InitializeTransformMatrix();
		GLuint GetVertexAttribute(const std::string& attributeName);
		GLuint GetUniformLocation(const std::string& uniformName);
	//protected:

	public:
		/*GameWorld(GLFWwindow * window, std::string vertexShaderPath, std::string fragmentShaderPath)
			: window(window), vertexShaderPath(vertexShaderPath), fragmentShaderPath(fragmentShaderPath)
		{

		}*/
		World(std::string windowName, GLint windowWidth, GLint windowHeight, std::string vertexShaderPath, std::string fragmentShaderPath)
			: name(windowName), width(windowWidth), height(windowHeight), vertexShaderPath(vertexShaderPath), fragmentShaderPath(fragmentShaderPath)
		{
			//InitializeGameWindow(); //Sets up GLFW window
			//InitializeShaderProgram(vertexShaderPath.c_str(), fragmentShaderPath.c_str()); //Compiles shaders
			//InitializeWorldObjects();
		}

		World(const World&) = delete; //Prevent copying the world
		World& operator=(const World&) = delete; //Prevent copying the world
		~World();

		void Initialize();//Sets up window, initializes glew, compiles shaders
		void Render();
		GLint GetWidth() const { return this->width; }
		GLint GetHeight() const { return this->height; }
		GLFWwindow & GetWindow() const { return *this->window; }
		GLint GetShaderProgramId() const { return this->shaderProgram->Program; }
		const std::string& GetName() const { return this->name; }
		void DoPlayerMovement(const Movement& movement, const GLfloat& deltaTime);
	};
}

