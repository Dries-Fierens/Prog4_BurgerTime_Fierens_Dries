#pragma once
#include <memory>
#include <string>
#include <vector>
#include <SDL3/SDL.h>
#include "GameManager.h"
#include "GameObject.h"
#include "LevelData.h"
#include "Font.h"

class Level final
{
public:
	static std::vector<std::unique_ptr<dae::GameObject>> Create(int levelNumber);

private:
	static std::unique_ptr<dae::GameObject> CreateTextObject(const std::string& text,
		const std::shared_ptr<dae::Font>& font, float x, float y, const SDL_Color& color);
	static std::string GetBackgroundTexture(int levelNumber);
	static std::vector<float> GetDropStops(const BurgerPartData& burgerPart,
		const BurgerStackData& burgerStack,
		const std::vector<PlatformData>& platforms,
		size_t stackIndex,
		size_t stackSize);
	static glm::vec2 GetPlayerSpawnPosition(const glm::vec2& spawnPosition);
	static glm::vec2 GetEnemySpawnPosition(const glm::vec2& spawnPosition);

	static constexpr float PlayerWidth{ 32.f };
	static constexpr float PlayerHeight{ 32.f };
	static constexpr float EnemyHeight{ 32.f };
	static constexpr float IngredientHeight{ 32.f };
};