#include "Texture.h"


namespace GameWorld
{
	void Texture::SetupTexture()
	{
		if (LoadImage())
		{
			glGenTextures(1, &this->index);
			glBindTexture(GL_TEXTURE_2D, this->index);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->width, this->height, 0, GL_RGB, GL_UNSIGNED_BYTE, this->image);
			// Set the texture wrapping parameters
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); //Set texture wrapping to GL_REPEAT (usually basic wrapping method)
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			// Set texture filtering parameters
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->width, this->height, 0, GL_RGB, GL_UNSIGNED_BYTE, this->image);
			glGenerateMipmap(GL_TEXTURE_2D);
			SOIL_free_image_data(this->image);
			glBindTexture(GL_TEXTURE_2D, 0); //Unbind texture when done, so we won't accidentily mess up our texture.
		}
		else
		{
			std::cerr << "ERROR: Failed to load texture image @ ' " << this->filePath << " '. Please check file path." << std::endl;
		}
	}

	Texture::Texture(const std::string& imageFilePath) : filePath(imageFilePath)
	{
		SetupTexture(); //Should I really be doing this as part of object construction???
	}

	/*void Texture::SetupTexture(const std::string & imageFilePath)
	{
		this->filePath = imageFilePath;
		this->SetupTexture();
	}*/

	bool Texture::LoadImage()
	{
		this->image = SOIL_load_image(this->filePath.c_str(), &this->width, &this->height, 0, SOIL_LOAD_RGB);
		if (this->image)
			return true;
		else
			return false;
	}
}
