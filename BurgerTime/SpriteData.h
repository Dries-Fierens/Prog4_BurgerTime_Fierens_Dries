#pragma once
#include <SDL3/SDL.h>
#include "LevelData.h"

namespace BurgerTimeSprites
{
	enum class Facing
	{
		Left,
		Right
	};

	inline constexpr float CellSize{ 16.f };

	constexpr SDL_FRect MakeRect(float column, float row, float widthInCells = 1, float heightInCells = 1)
	{
		return SDL_FRect
		{
			column * CellSize,
			row * CellSize,
			widthInCells * CellSize,
			heightInCells * CellSize
		};
	}

	inline constexpr SDL_FRect PeterIdle{ MakeRect(5, 0) };
	inline constexpr SDL_FRect PeterWalk{ MakeRect(6, 0) };

	inline constexpr SDL_FRect SaltIdle{ MakeRect(5, 0) };
	inline constexpr SDL_FRect SaltWalk{ MakeRect(6, 0) };

	inline constexpr SDL_FRect HotDogIdle{ MakeRect(0, 3) };
	inline constexpr SDL_FRect PickleIdle{ MakeRect(0, 5) };
	inline constexpr SDL_FRect EggIdle{ MakeRect(0, 7) };

	// Ingredients are half a cell high
	inline constexpr SDL_FRect TopBun{ MakeRect(7, 3, 2, 0.5f) };
	inline constexpr SDL_FRect BottomBun{ MakeRect(7, 3.5f, 2, 0.5f) };
	inline constexpr SDL_FRect Cheese{ MakeRect(7, 4, 2, 0.5f) };
	inline constexpr SDL_FRect Patty{ MakeRect(7, 4.5f, 2, 0.5f) };
	inline constexpr SDL_FRect Tomato{ MakeRect(7, 5, 2, 0.5f) };
	inline constexpr SDL_FRect Lettuce{ MakeRect(7, 5.5f, 2, 0.5f) };

	inline constexpr SDL_FRect PepperCloud{ MakeRect(12, 2, 4, 2) };

	inline SDL_FRect GetPlayerFrame(int playerIndex, bool isMoving, int animationFrame)
	{
		const bool useWalkFrame = isMoving && (animationFrame % 2 == 1);

		if (playerIndex == 2)
		{
			return useWalkFrame ? SaltWalk : SaltIdle;
		}

		return useWalkFrame ? PeterWalk : PeterIdle;
	}

	inline SDL_FRect GetEnemyFrame(EnemyType type)
	{
		switch (type)
		{
		case EnemyType::HotDog:
			return HotDogIdle;
		case EnemyType::Pickle:
			return PickleIdle;
		case EnemyType::Egg:
			return EggIdle;
		default:
			return HotDogIdle;
		}
	}

	inline SDL_FRect GetIngredientFrame(IngredientType type)
	{
		switch (type)
		{
		case IngredientType::TopBun:
			return TopBun;
		case IngredientType::BottomBun:
			return BottomBun;
		case IngredientType::Patty:
			return Patty;
		case IngredientType::Cheese:
			return Cheese;
		case IngredientType::Lettuce:
			return Lettuce;
		case IngredientType::Tomato:
			return Tomato;
		default:
			return Patty;
		}
	}

	inline SDL_FRect GetPepperCloudFrame()
	{
		return PepperCloud;
	}
}