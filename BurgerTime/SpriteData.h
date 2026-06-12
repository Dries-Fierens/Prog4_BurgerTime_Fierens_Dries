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

	constexpr SDL_FRect MakeRect(int column, int row, int widthInCells = 1, int heightInCells = 1)
	{
		return SDL_FRect
		{
			static_cast<float>(column) * CellSize,
			static_cast<float>(row) * CellSize,
			static_cast<float>(widthInCells) * CellSize,
			static_cast<float>(heightInCells) * CellSize
		};
	}

	inline constexpr SDL_FRect PeterIdleRight{ MakeRect(5, 0) };
	inline constexpr SDL_FRect PeterWalkRight{ MakeRect(6, 0) };
	inline constexpr SDL_FRect PeterIdleLeft{ MakeRect(5, 0) };
	inline constexpr SDL_FRect PeterWalkLeft{ MakeRect(6, 0) };

	inline constexpr SDL_FRect SaltIdleRight{ MakeRect(5, 0) };
	inline constexpr SDL_FRect SaltWalkRight{ MakeRect(6, 0) };
	inline constexpr SDL_FRect SaltIdleLeft{ MakeRect(5, 0) };
	inline constexpr SDL_FRect SaltWalkLeft{ MakeRect(6, 0) };

	inline constexpr SDL_FRect HotDogIdle{ MakeRect(0, 3) };
	inline constexpr SDL_FRect PickleIdle{ MakeRect(0, 5) };
	inline constexpr SDL_FRect EggIdle{ MakeRect(0, 7) };

	inline constexpr SDL_FRect TopBun{ MakeRect(8, 0, 4, 1) };
	inline constexpr SDL_FRect BottomBun{ MakeRect(8, 1, 4, 1) };
	inline constexpr SDL_FRect Patty{ MakeRect(8, 2, 4, 1) };
	inline constexpr SDL_FRect Cheese{ MakeRect(8, 3, 4, 1) };
	inline constexpr SDL_FRect Lettuce{ MakeRect(8, 4, 4, 1) };
	inline constexpr SDL_FRect Tomato{ MakeRect(8, 5, 4, 1) };
	inline constexpr SDL_FRect Plate{ MakeRect(8, 6, 4, 1) };

	inline SDL_FRect GetPlayerFrame(int playerIndex, Facing facing, bool isMoving, int animationFrame)
	{
		const bool useWalkFrame = isMoving && (animationFrame % 2 == 1);

		if (playerIndex == 2)
		{
			if (facing == Facing::Left)
			{
				return useWalkFrame ? SaltWalkLeft : SaltIdleLeft;
			}

			return useWalkFrame ? SaltWalkRight : SaltIdleRight;
		}

		if (facing == Facing::Left)
		{
			return useWalkFrame ? PeterWalkLeft : PeterIdleLeft;
		}

		return useWalkFrame ? PeterWalkRight : PeterIdleRight;
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

	inline SDL_FRect GetPlateFrame()
	{
		return Plate;
	}
}