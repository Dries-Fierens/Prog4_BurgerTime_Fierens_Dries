#pragma once

//Compiled from the original game rules and scoring system of BurgerTime
namespace BurgerTimeRules
{
	// Inline constexprs means that these values are compile-time constants and can be used in constant expressions. They also have internal linkage, meaning they are only visible within the translation unit where they are defined.
	inline constexpr int StartingLives{ 3 };
	inline constexpr int StartingPepperShots{ 5 };
	inline constexpr int TotalBoards{ 3 };

	inline constexpr int ScorePerStoryPerPart{ 50 };

	inline constexpr int HotDogScore{ 100 };
	inline constexpr int PickleScore{ 200 };
	inline constexpr int EggScore{ 300 };

	constexpr int GetDroppedEnemyBonus(int enemyCount)
	{
		switch (enemyCount)
		{
		case 1:
			return 500;
		case 2:
			return 1000;
		case 3:
			return 2000;
		case 4:
			return 4000;
		case 5:
			return 8000;
		default:
			return enemyCount >= 6 ? 16000 : 0;
		}
	}
}