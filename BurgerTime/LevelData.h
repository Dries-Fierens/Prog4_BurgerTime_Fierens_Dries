#pragma once
#include <glm/vec2.hpp>
#include <vector>

enum class IngredientType
{
	TopBun,
	BottomBun,
	Patty,
	Cheese,
	Lettuce,
	Tomato
};

enum class EnemyType
{
	HotDog,
	Pickle,
	Egg
};

struct PlatformData final
{
	glm::vec2 position{};
	float width{};
};

struct LadderData final
{
	glm::vec2 position{};
	float height{};
};

struct BurgerPartData final
{
	IngredientType type{};
	glm::vec2 position{};
	float width{};
};

struct BurgerStackData final
{
	glm::vec2 platePosition{};
	std::vector<BurgerPartData> parts{};
};

struct EnemySpawn final
{
	EnemyType type{};
	glm::vec2 position{};
};

struct PlayerSpawn final
{
	glm::vec2 playerOne{};
	glm::vec2 playerTwo{};
	glm::vec2 versusEnemy{};
};

struct LevelLayout final
{
	int number{};
	PlayerSpawn playerSpawns{};
	std::vector<PlatformData> platforms{};
	std::vector<LadderData> ladders{};
	std::vector<BurgerStackData> burgerStacks{};
	std::vector<EnemySpawn> enemySpawns{};
};

const LevelLayout& GetLevelLayout(int levelNumber);
const std::vector<LevelLayout>& GetAllLevelLayouts();