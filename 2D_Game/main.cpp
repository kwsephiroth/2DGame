#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
//#include "Shader.h"
//#include <SOIL/SOIL.h>
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//#include <glm/ext.hpp>
#include <stdio.h>
#include "GameWorld.h"
#include "GameEnums.h"
#include <algorithm>
#include <windows.h>


//Globals
GLuint screenWidth = 800, screenHeight = 600;
bool keys[1024];
GLfloat lastX = 400, lastY = 300;
GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;

// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void DoCharacterMovement(GameWorld::World& gameWorld);
void resize_callback(GLFWwindow* window, int width, int height);

int main(int argc, char* argv[])
{
	//GameWorld::WorldObjects::Ground c;
	// Define the viewport dimensions
	glViewport(0, 0, screenWidth, screenHeight);

	GameWorld::World gameWorld("", screenWidth, screenHeight, "vertexShader.vs", "fragmentShader.frag");
	gameWorld.Initialize(); //Sets up window, initialize glew, compiles shaders. TO DO: May need to return error code on failure...

	//Set up callback functions to capture and respond to events
	glfwSetKeyCallback(&gameWorld.GetWindow(), key_callback);
	glfwSetWindowSizeCallback(&gameWorld.GetWindow(), [](GLFWwindow* window, int width, int height) { glViewport(0, 0, width, height); });

	GLfloat minFrameTime = 1.0f / 60.0f;
	GLfloat sleepTime = 0.0f;

	//Game Loop
	while (!glfwWindowShouldClose(&gameWorld.GetWindow())) //Draw frames until window is closed
	{
		// Set frame time
		GLfloat currentFrame = (float)glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// Check and call events
		glfwPollEvents(); //Any pressed keys will be recorded

		/*if (minFrameTime > 0)
		{
			sleepTime += minFrameTime - deltaTime;
			sleepTime = sleepTime >= 0 ? sleepTime : 0;//substitute for max function
			Sleep(sleepTime);
		}*/


			//Handle any movement commands
			DoCharacterMovement(gameWorld);
			//if (!keys[GLFW_KEY_W]) //If not a player jump command
			//{
				// Clear the colorbuffer
				glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
				glClear(GL_COLOR_BUFFER_BIT); //| GL_DEPTH_BUFFER_BIT);
				gameWorld.Render(); //Draw one frame
			/*}*/Sleep(100.0f);//temp

		//else //Perform jump animation
		//{

		//}
	}
	return 0;
}

void DoCharacterMovement(GameWorld::World& gameWorld) //TO DO: Will need to update the frame/position of the character sprite only
{
	if (keys[GLFW_KEY_W]) //UP Movement
	{
		gameWorld.DoPlayerMovement(GameWorld::Movement::UP, deltaTime);
	}
	if (keys[GLFW_KEY_S])//DOWN/Crouch Movement
	{
		gameWorld.DoPlayerMovement(GameWorld::Movement::DOWN, deltaTime);
	}
	if (keys[GLFW_KEY_A])//LEFT movement
	{
		gameWorld.DoPlayerMovement(GameWorld::Movement::LEFT, deltaTime);
	}
	if (keys[GLFW_KEY_D])//RIGHT movement
	{
		gameWorld.DoPlayerMovement(GameWorld::Movement::RIGHT, deltaTime);
	}
	/*if (keys[GLFW_KEY_SPACE])//JUMP movement
	{
		gameWorld.DoCharacterMovement(GameWorld::Movement::JUMP, deltaTime);
	}*/
}

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	//cout << key << endl;
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			keys[key] = true;
		else if (action == GLFW_RELEASE)
			keys[key] = false;
	}
}


void resize_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}