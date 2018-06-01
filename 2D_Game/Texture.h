#pragma once
#include <GL/glew.h>
#include <SOIL/SOIL.h>
#include <string>
#include <iostream>
#include <stdio.h>
#include <vector>

namespace GameWorld
{
	class Texture
	{
	private:
		int height;
		int width;
		GLuint index;
		std::string filePath;
		unsigned char* image; //Raw pointer!!! Either eliminate, write custom copy constructor and assignment operator, or disable copying
		void SetupTexture();
		bool LoadImage();
	public:
		//Texture() = default;
		Texture(const std::string& imageFilePath);

		//Copy constructor and assignment operator
		Texture(const Texture& source)
		{
			if (&source == this)
				return;

			this->height = source.height;
			this->width = source.width;
			memcpy(this->image, source.image, sizeof(this->image));
			this->index = source.index;
			this->filePath = source.filePath;
		}
		Texture& operator=(const Texture& source)
		{
			if (&source == this)
				return *this;

			this->height = source.height;
			this->width = source.width;

			memcpy(this->image, source.image, sizeof(source.image));

			this->index = source.index;
			this->filePath = source.filePath;

			return *this;
		}

		//TO DO: Should I allow or disallow MOVE operations????

		~Texture() { }

		//void SetupTexture(const std::string & imageFilePath);
		GLuint GetIndex() const { return this->index; }
		int GetHeight() const { return this->height; }
		int GetWidth() const  { return this->width; }
		const std::string& GetFilePath() const { return this->filePath; }
	};
}

