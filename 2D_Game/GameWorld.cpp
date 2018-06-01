#include "GameWorld.h"


namespace GameWorld
{
	World::~World()
	{
		shaderProgram = nullptr;
		delete shaderProgram;

		//Free memory from pointers
		for (auto& obj : this->worldObjects)
		{
			delete obj;
		}
		this->worldObjects.clear();
	}

	void World::Initialize()
	{
		InitializeGameWindow(); //Sets up GLFW window
		InitializeGlew(); //Initializes Glew - Must be done after window initialized
		InitializeShaderProgram(); //Compiles shaders
		InitializeWorldObjects();

		this->shaderProgram->Use(); //Do I really need to call this repeatedly?
		InitializeTransformMatrix();
	}

	void World::Render()
	{

		for (auto& obj : worldObjects)
		{
			obj->Draw(); //Draws object for the current frame
			InitializeTransformMatrix(); //Resets transform matrix
		}
		glfwSwapBuffers(this->window);
	}

	void World::InitializeGameWindow()
	{
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
		glfwWindowHint(GLFW_SAMPLES, 4);

		//this->window = std::make_unique<GLFWwindow>(glfwCreateWindow(this->width, this->height, this->name.c_str(), nullptr, nullptr));
		this->window = glfwCreateWindow(this->width, this->height, this->name.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(this->window);
	}

	void World::InitializeShaderProgram()//const GLchar* vertexShaderPath, const GLchar* fragmentShaderPath)
	{
		//this->shaderProgram = std::make_unique<Shader>(new Shader("vertexShader.vs", "fragmentShader.frag"));
		this->shaderProgram = new Shader(this->vertexShaderPath.c_str(), fragmentShaderPath.c_str());
	}

	void World::InitializeGlew()
	{
		// Initialize GLEW to setup the OpenGL Function pointers
		glewExperimental = GL_TRUE;

		if (glewInit() != GLEW_OK)
		{
			std::cerr << "ERROR: Failed to initialize GLEW!" << std::endl;
			exit(0);
		}
	}

	void World::InitializeWorldObjects()
	{
		this->worldObjects.emplace_back(new Player(GetVertexAttribute("position"), GetVertexAttribute("color"), GetVertexAttribute("texCoord")));
		//this->worldObjects.emplace_back(new Ground(GetVertexAttribute("position"), GetVertexAttribute("color"), GetVertexAttribute("texCoord")));
		//glBindVertexArray(this->worldObjects[0]->GetVAO());
		//glEnableVertexAttribArray(0); //position
		//glEnableVertexAttribArray(1); //color
		//glBindVertexArray(0);
	}

	void World::InitializeTransformMatrix()
	{
		glm::mat4 transform; //Reset to identity matrix
		GLuint transLoc = GetUniformLocation("transform");
		glUniformMatrix4fv(transLoc, 1, GL_FALSE, glm::value_ptr(transform));
	}

	GLuint World::GetVertexAttribute(const std::string&  attributeName)
	{
		if (this->shaderProgram)
		{
			return glGetAttribLocation(this->shaderProgram->Program, attributeName.c_str());
		}
		else
		{
			throw "ERROR: Shader program has not been initialized.";
		}
	}

	GLuint World::GetUniformLocation(const std::string&  uniformName)
	{
		if (this->shaderProgram)
		{
			return glGetUniformLocation(this->shaderProgram->Program, uniformName.c_str());
		}
		else
		{
			throw "ERROR: Shader program has not been initialized.";
		}

	}

	void World::DoPlayerMovement(const Movement & movement, const GLfloat & deltaTime)
	{
		for (auto& obj : this->worldObjects) //TODO: NOT EFFICENT!! SWITCH TO HASH MAP FOR FAST LOOKUP
		{
			if (obj->GetType() == WorldObjectType::PLAYER)
			{
			   GLuint transLoc = GetUniformLocation("transform");
			   obj->DoMovement(transLoc, movement, deltaTime);
			}
		}
	}
}