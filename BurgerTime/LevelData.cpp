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
			{ { 0.f, 90.f }, 624.f },
			{ { 0.f, 138.f }, 335.f },
			{ { 432.f, 138.f }, 192.f },
			{ { 0.f, 185.f }, 624.f },
			{ { 288.f, 234.f }, 192.f },
			{ { 144.f, 282.f }, 335.f },
			{ { 0.f, 378.f }, 192.f },
			{ { 430.f, 378.f }, 192.f },
			{ { 0.f, 424.f }, 192.f },
			{ { 430.f, 424.f }, 192.f },
			{ { 0.f, 473.f }, 192.f },
			{ { 430.f, 473.f }, 192.f },
			{ { 144.f, 522.f }, 335.f },
			{ { 144.f, 569.f }, 335.f }
		},
		{
			{ { 24.f, 42.f }, 192.f },
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
			{ { 0.f, 90.f }, 335.f },
			{ { 288.f, 138.f }, 335.f },
			{ { 0.f, 138.f }, 195.f },
			{ { 144.f, 185.f }, 192.f },
			{ { 432.f, 185.f }, 192.f },
			{ { 0.f, 234.f }, 624.f },
			{ { 288.f, 282.f }, 192.f },
			{ { 144.f, 330.f }, 192.f },
			{ { 288.f, 378.f }, 192.f },
			{ { 144.f, 425.f }, 335.f }
		},
		{
			{ { 24.f, 42.f }, 192.f },
			{ { 96.f, 42.f }, 192.f },
			{ { 168.f, 42.f }, 192.f },
			{ { 240.f, 42.f }, 390.f },
			{ { 312.f, 42.f }, 484.f },
			{ { 384.f, 42.f }, 390.f },
			{ { 456.f, 42.f }, 192.f },
			{ { 528.f, 42.f }, 192.f },
			{ { 600.f, 42.f }, 192.f }
		},
		{
			MakeBurgerStack(
				{ 48.f, 430.f },
				{
					{ IngredientType::TopBun, { 48.f, 22.f }, 100.f },
					{ IngredientType::Cheese, { 48.f, 65.f }, 100.f },
					{ IngredientType::Patty, { 48.f, 115.f }, 100.f },
					{ IngredientType::BottomBun, { 48.f, 210.f }, 100.f }
				}),
			MakeBurgerStack(
				{ 192.f, 560.f },
				{
					{ IngredientType::TopBun, { 192.f, 22.f }, 100.f },
					{ IngredientType::Lettuce, { 192.f, 65.f }, 100.f },
					{ IngredientType::Patty, { 192.f, 165.f }, 100.f },
					{ IngredientType::BottomBun, { 192.f, 210.f }, 100.f }
				}),
			MakeBurgerStack(
				{ 340.f, 560.f },
				{
					{ IngredientType::TopBun, { 340.f, 22.f }, 100.f },
					{ IngredientType::Tomato, { 340.f, 115.f }, 100.f },
					{ IngredientType::Patty, { 340.f, 215.f }, 100.f },
					{ IngredientType::BottomBun, { 340.f, 250.f }, 100.f }
				}),
			MakeBurgerStack(
				{ 484.f, 430.f },
				{
					{ IngredientType::TopBun, { 484.f, 22.f }, 100.f },
					{ IngredientType::Lettuce, { 484.f, 115.f }, 100.f },
					{ IngredientType::Patty, { 484.f, 165.f }, 100.f },
					{ IngredientType::BottomBun, { 484.f, 210.f }, 100.f }
				})
		},
		{
			{ EnemyType::HotDog, { 220.f, 42.f } },
			{ EnemyType::Pickle, { 432.f, 42.f } },
			{ EnemyType::Egg, { 336.f, 42.f } }
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
					{ IngredientType::Lettuce, { 48.f, 207.f }, 100.f },
					{ IngredientType::Patty, { 48.f, 350.f }, 100.f },
					{ IngredientType::BottomBun, { 48.f, 450.f }, 100.f }
				}),
			MakeBurgerStack(
				{ 192.f, 560.f },
				{
					{ IngredientType::TopBun, { 192.f, 22.f }, 100.f },
					{ IngredientType::Lettuce, { 192.f, 250.f }, 100.f },
					{ IngredientType::Patty, { 192.f, 350.f }, 100.f },
					{ IngredientType::BottomBun, { 192.f, 450.f }, 100.f }
				}),
			MakeBurgerStack(
				{ 340.f, 560.f },
				{
					{ IngredientType::TopBun, { 340.f, 22.f }, 100.f },
					{ IngredientType::Lettuce, { 340.f, 250.f }, 100.f },
					{ IngredientType::Patty, { 340.f, 350.f }, 100.f },
					{ IngredientType::BottomBun, { 340.f, 450.f }, 100.f }
				}),
			MakeBurgerStack(
				{ 484.f, 560.f },
				{
					{ IngredientType::TopBun, { 484.f, 22.f }, 100.f },
					{ IngredientType::Lettuce, { 484.f, 207.f }, 100.f },
					{ IngredientType::Patty, { 484.f, 305.f }, 100.f },
					{ IngredientType::BottomBun, { 484.f, 450.f }, 100.f }
				})
		},
		{
			{ EnemyType::Pickle, { 490.f, 240.f } },
			{ EnemyType::Egg, { 332.f, 42.f } }
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