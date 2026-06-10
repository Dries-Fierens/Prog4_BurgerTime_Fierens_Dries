#include "LevelData.h"
#include <cstddef>
#include <initializer_list>
#include <vector>

static BurgerStackData MakeBurgerStack(const glm::vec2& platePosition, std::initializer_list<BurgerPartData> parts)
{
	return BurgerStackData
	{
		platePosition,
		std::vector<BurgerPartData>{ parts }
	};
}

static LevelLayout CreateLevelThree()
{
	return LevelLayout
	{
		3,
		{
			{ 48.f, 458.f },
			{ 240.f, 458.f },
			{ 456.f, 106.f }
		},
		{
			{ { 0.f, 42.f }, 624.f },
			{ { 0.f, 106.f }, 624.f },
			{ { 0.f, 170.f }, 624.f },
			{ { 144.f, 234.f }, 336.f },
			{ { 144.f, 298.f }, 192.f },
			{ { 0.f, 394.f }, 192.f },
			{ { 456.f, 394.f }, 168.f },
			{ { 0.f, 458.f }, 288.f },
			{ { 456.f, 458.f }, 168.f },
			{ { 192.f, 522.f }, 288.f }
		},
		{
			{ { 24.f, 42.f }, 128.f },
			{ { 144.f, 42.f }, 480.f },
			{ { 216.f, 42.f }, 64.f },
			{ { 312.f, 42.f }, 256.f },
			{ { 312.f, 458.f }, 64.f },
			{ { 384.f, 170.f }, 64.f },
			{ { 456.f, 42.f }, 480.f },
			{ { 72.f, 394.f }, 64.f },
			{ { 552.f, 42.f }, 128.f },
			{ { 552.f, 394.f }, 64.f }
		},
		{
			MakeBurgerStack(
				{ 72.f, 560.f },
				{
					{ IngredientType::TopBun, { 72.f, 74.f }, 72.f },
					{ IngredientType::Patty, { 72.f, 202.f }, 72.f },
					{ IngredientType::Lettuce, { 72.f, 362.f }, 72.f },
					{ IngredientType::BottomBun, { 72.f, 490.f }, 72.f }
				}),
			MakeBurgerStack(
				{ 408.f, 560.f },
				{
					{ IngredientType::TopBun, { 408.f, 74.f }, 72.f },
					{ IngredientType::Cheese, { 408.f, 202.f }, 72.f },
					{ IngredientType::Patty, { 408.f, 362.f }, 72.f },
					{ IngredientType::BottomBun, { 408.f, 490.f }, 72.f }
				})
		},
		{
			{ EnemyType::HotDog, { 240.f, 106.f } },
			{ EnemyType::Pickle, { 408.f, 234.f } }
		}
	};
}

static LevelLayout CreateLevelTwo()
{
	return LevelLayout
	{
		2,
		{
			{ 288.f, 426.f },
			{ 336.f, 426.f },
			{ 288.f, 42.f }
		},
		{
			{ { 0.f, 42.f }, 624.f },
			{ { 0.f, 106.f }, 336.f },
			{ { 288.f, 170.f }, 336.f },
			{ { 144.f, 234.f }, 192.f },
			{ { 288.f, 298.f }, 192.f },
			{ { 144.f, 362.f }, 336.f },
			{ { 288.f, 426.f }, 48.f }
		},
		{
			{ { 48.f, 42.f }, 64.f },
			{ { 96.f, 42.f }, 64.f },
			{ { 144.f, 42.f }, 192.f },
			{ { 216.f, 42.f }, 320.f },
			{ { 312.f, 42.f }, 384.f },
			{ { 384.f, 170.f }, 192.f },
			{ { 456.f, 42.f }, 320.f },
			{ { 552.f, 42.f }, 128.f },
			{ { 600.f, 42.f }, 128.f }
		},
		{
			MakeBurgerStack(
				{ 96.f, 560.f },
				{
					{ IngredientType::TopBun, { 96.f, 74.f }, 72.f },
					{ IngredientType::Cheese, { 96.f, 202.f }, 72.f },
					{ IngredientType::Patty, { 96.f, 330.f }, 72.f },
					{ IngredientType::BottomBun, { 96.f, 394.f }, 72.f }
				}),
			MakeBurgerStack(
				{ 264.f, 560.f },
				{
					{ IngredientType::TopBun, { 264.f, 138.f }, 72.f },
					{ IngredientType::Lettuce, { 264.f, 266.f }, 72.f },
					{ IngredientType::Patty, { 264.f, 330.f }, 72.f },
					{ IngredientType::BottomBun, { 264.f, 394.f }, 72.f }
				}),
			MakeBurgerStack(
				{ 432.f, 560.f },
				{
					{ IngredientType::TopBun, { 432.f, 138.f }, 72.f },
					{ IngredientType::Tomato, { 432.f, 266.f }, 72.f },
					{ IngredientType::Cheese, { 432.f, 330.f }, 72.f },
					{ IngredientType::BottomBun, { 432.f, 394.f }, 72.f }
				})
		},
		{
			{ EnemyType::HotDog, { 240.f, 106.f } },
			{ EnemyType::Pickle, { 432.f, 298.f } },
			{ EnemyType::Egg, { 336.f, 170.f } }
		}
	};
}

static LevelLayout CreateLevelOne()
{
	return LevelLayout
	{
		1,
		{
			{ 48.f, 472.f },
			{ 240.f, 472.f },
			{ 456.f, 106.f }
		},
		{
			{ { 0.f, 42.f }, 624.f },
			{ { 288.f, 138.f }, 335.f },
			{ { 0.f, 138.f }, 195.f },
			{ { 144.f, 185.f }, 192.f },
			{ { 0.f, 234.f }, 192.f },
			{ { 432.f, 234.f }, 192.f },
			{ { 145.f, 282.f }, 335.f },
			{ { 432.f, 330.f }, 192.f },
			{ { 0.f, 378.f }, 480.f },
			{ { 0.f, 473.f }, 624.f }
		},
		{
			{ { 24.f, 42.f }, 95.f },
			{ { 24.f, 235.f }, 240.f },
			{ { 95.f, 140.f }, 240.f },
			{ { 168.f, 42.f }, 430.f },
			{ { 240.f, 42.f }, 148.f },
			{ { 312.f, 42.f }, 430.f },
			{ { 384.f, 138.f }, 148.f },
			{ { 456.f, 42.f }, 430.f },
			{ { 528.f, 234.f }, 240.f },
			{ { 600.f, 42.f }, 186.f },
			{ { 600.f, 332.f }, 138.f }
		},
		{
			MakeBurgerStack(
				{ 48.f, 560.f },
				{
					{ IngredientType::TopBun, { 48.f, 108.f }, 100.f },
					{ IngredientType::Lettuce, { 48.f, 202.f }, 100.f },
					{ IngredientType::Patty, { 48.f, 330.f }, 100.f },
					{ IngredientType::BottomBun, { 48.f, 450.f }, 100.f }
				}),
			MakeBurgerStack(
				{ 192.f, 560.f },
				{
					{ IngredientType::TopBun, { 192.f, 12.f }, 100.f },
					{ IngredientType::Lettuce, { 192.f, 242.f }, 100.f },
					{ IngredientType::Patty, { 192.f, 330.f }, 100.f },
					{ IngredientType::BottomBun, { 192.f, 450.f }, 100.f }
				}),
			MakeBurgerStack(
				{ 360.f, 560.f },
				{
					{ IngredientType::TopBun, { 360.f, 12.f }, 100.f },
					{ IngredientType::Lettuce, { 360.f, 246.f }, 100.f },
					{ IngredientType::Patty, { 360.f, 394.f }, 100.f },
					{ IngredientType::BottomBun, { 360.f, 450.f }, 100.f }
				}),
			MakeBurgerStack(
				{ 504.f, 560.f },
				{
					{ IngredientType::TopBun, { 504.f, 12.f }, 100.f },
					{ IngredientType::Lettuce, { 504.f, 330.f }, 100.f },
					{ IngredientType::Patty, { 504.f, 394.f }, 100.f },
					{ IngredientType::BottomBun, { 504.f, 450.f }, 100.f }
				})
		},
		{
			{ EnemyType::HotDog, { 456.f, 106.f } },
			//{ EnemyType::HotDog, { 216.f, 170.f } },
			//{ EnemyType::Pickle, { 456.f, 298.f } },
			//{ EnemyType::Egg, { 312.f, 234.f } }
		}
	};
}

const std::vector<LevelLayout>& GetAllLevelLayouts()
{
	static const std::vector<LevelLayout> levelLayouts
	{
		CreateLevelOne(),
		CreateLevelTwo(),
		CreateLevelThree()
	};

	return levelLayouts;
}

const LevelLayout& GetLevelLayout(int levelNumber)
{
	const auto& levelLayouts = GetAllLevelLayouts();

	if (levelNumber <= 1)
	{
		return levelLayouts.front();
	}

	const auto index = static_cast<std::size_t>(levelNumber - 1);
	if (index >= levelLayouts.size())
	{
		return levelLayouts.back();
	}

	return levelLayouts[index];
}