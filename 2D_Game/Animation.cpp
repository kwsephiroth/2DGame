#include "Animation.h"


namespace GameWorld
{
	void Animation::SetupFrames(const std::vector<Texture*>& textures)
	{
		unsigned int frameIndex = 0;
		for (auto& t : textures)
		{
			this->frames.emplace_back(new AnimationFrame(frameIndex, *t));
			frameIndex++;
		}
	}

	Animation::~Animation()
	{
		//Free memory from pointers
		for (auto& f : this->frames)
		{
			delete f;
		}
		this->frames.clear();
	}
}
