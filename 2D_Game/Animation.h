#pragma once
#include "Texture.h"
#include <vector>
#include <iostream>
#include <memory>
#include "GameEnums.h"

namespace GameWorld
{
	class AnimationFrame;

	class Animation
	{
	private:
		AnimationType type;
		std::vector<AnimationFrame*> frames;//TODO: Switch to vector of smart pointers
		void SetupFrames(const std::vector<Texture*>& textures);
	public:
		Animation(AnimationType animationType, const std::vector<Texture*>& textures) : type(animationType)
		{
			SetupFrames(textures);
		}
		~Animation();
		const AnimationType GetType() const { return this->type; }
		const auto& GetFrames() const { return this->frames; }
	};

	class AnimationFrame
	{
	private:
		unsigned int index;
		std::unique_ptr<Texture> texture;
	public:
		AnimationFrame(const unsigned int frameIndex, const Texture frameTexture) : index(frameIndex),
			texture(std::make_unique<Texture>(frameTexture)) {}
		~AnimationFrame() {}
		unsigned int GetIndex() const { return this->index; }
		const auto& GetTexture() const { return this->texture; }
	};
}

