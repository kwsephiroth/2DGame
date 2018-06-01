#pragma once

namespace GameWorld
{
	enum class WorldObjectType
	{
		BACKGROUND,
		PLATFORM,
		GROUND,
		PLAYER,
		ENEMY
	};

	enum class CharacterType
	{
		PLAYER,
		ENEMY
	};

	enum class GameWorldErrorCode
	{
		GAMEWORLDINIT_OK,
		GAMEWORLDINIT_FAIL
	};

	enum class Movement
	{
		UP,
		DOWN,
		LEFT,
		RIGHT,
		JUMP
	};

	enum class AnimationType
	{
		PLAYER_STAND,
		PLAYER_WALK,
		PLAYER_ATTACK,
		PLAYER_JUMP,
		PLAYER_FALL,
		PLAYER_HURT,
		PLAYER_DEATH,
		PLAYER_WIN
	};
}

