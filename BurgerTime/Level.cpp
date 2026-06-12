#include "Level.h"
#include "BoardComponent.h"
#include "BurgerIngredientComponent.h"
#include "BurgerIngredientSpriteComponent.h"
#include "BurgerProgressComponent.h"
#include "Enemy.h"
#include "FPSCounter.h"
#include "GameManager.h"
#include "GameObject.h"
#include "Player.h"
#include "RenderComponent.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "SpriteComponent.h"
#include "SpriteData.h"
#include "TextComponent.h"
#include <algorithm>
#include <sstream>

std::vector<float> Level::GetDropStops(const BurgerPartData& burgerPart,
	const BurgerStackData& burgerStack,
	const std::vector<PlatformData>& platforms)
{
	std::vector<float> dropStops{};
	const float ingredientCenterX = burgerPart.position.x + burgerPart.width * 0.5f;

	for (const auto& platform : platforms)
	{
		if (platform.position.y <= burgerPart.position.y + IngredientHeight)
		{
			continue;
		}

		const float left = platform.position.x;
		const float right = platform.position.x + platform.width;

		if (ingredientCenterX >= left && ingredientCenterX <= right)
		{
			dropStops.push_back(platform.position.y - IngredientHeight);
		}
	}

	dropStops.push_back(burgerStack.platePosition.y);

	std::sort(dropStops.begin(), dropStops.end());
	dropStops.erase(std::unique(dropStops.begin(), dropStops.end()), dropStops.end());

	return dropStops;
}

glm::vec2 Level::GetPlayerSpawnPosition(const glm::vec2& spawnPosition)
{
	return { spawnPosition.x, spawnPosition.y - PlayerHeight };
}

glm::vec2 Level::GetEnemySpawnPosition(const glm::vec2& spawnPosition)
{
	return { spawnPosition.x, spawnPosition.y - EnemyHeight };
}

std::vector<std::unique_ptr<dae::GameObject>> Level::Create(int levelNumber)
{
	std::vector<std::unique_ptr<dae::GameObject>> level{};

	const auto& levelLayout = GetLevelLayout(levelNumber);
	const glm::vec2 windowSize = dae::Renderer::GetInstance().GetWindowSize();

	auto backgroundObject = std::make_unique<dae::GameObject>();
	auto background = std::make_unique<dae::RenderComponent>(GetBackgroundTexture(levelLayout.number), backgroundObject.get());
	backgroundObject->AddComponent(std::move(background));
	level.push_back(std::move(backgroundObject));

	auto boardObject = std::make_unique<dae::GameObject>();
	boardObject->AddComponent(std::make_unique<BoardComponent>(levelLayout.platforms, levelLayout.ladders, boardObject.get()));
	auto* burgerProgress = boardObject->AddComponent(std::make_unique<BurgerProgressComponent>(boardObject.get()));
	level.push_back(std::move(boardObject));

	const auto infoFont = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);

	auto fpsObject = std::make_unique<dae::GameObject>();
	auto fpsComponent = std::make_unique<dae::FPSCounter>(infoFont, fpsObject.get());
	fpsObject->AddComponent(std::move(fpsComponent));
	fpsObject->SetLocalPosition(10.f, 10.f);
	level.push_back(std::move(fpsObject));

	std::vector<BurgerIngredientComponent*> ingredientComponents{};

	for (const auto& burgerStack : levelLayout.burgerStacks)
	{
		auto sortedParts = burgerStack.parts;
		std::sort(sortedParts.begin(), sortedParts.end(),
			[](const BurgerPartData& left, const BurgerPartData& right)
			{
				return left.position.y < right.position.y;
			});

		std::vector<BurgerIngredientComponent*> stackIngredients{};

		for (const auto& part : sortedParts)
		{
			auto ingredientObject = std::make_unique<dae::GameObject>();

			ingredientObject->AddComponent(std::make_unique<BurgerIngredientSpriteComponent>(
				part.type, part.width, IngredientHeight, ingredientObject.get()));

			auto* ingredient = ingredientObject->AddComponent(std::make_unique<BurgerIngredientComponent>(
				part.type,
				part.width,
				GetDropStops(part, burgerStack, levelLayout.platforms),
				ingredientObject.get()));

			ingredientObject->SetLocalPosition(part.position.x, part.position.y);

			stackIngredients.push_back(ingredient);
			ingredientComponents.push_back(ingredient);
			level.push_back(std::move(ingredientObject));
		}

		for (size_t index{}; index + 1 < stackIngredients.size(); ++index)
		{
			stackIngredients[index]->SetIngredientBelow(stackIngredients[index + 1]);
		}
	}

	burgerProgress->SetIngredients(ingredientComponents);

	for (const auto& enemySpawn : levelLayout.enemySpawns)
	{
		const glm::vec2 spawnPosition = GetEnemySpawnPosition(enemySpawn.position);
		level.push_back(Enemy::Create(enemySpawn.type, spawnPosition.x, spawnPosition.y));
	}

	const float leftUiX{ 10.f };
	const float rightUiX{ windowSize.x - 140.f };
	const float uiY{ 504.f };

	switch (GameManager::GetInstance().GetGameState())
	{
	case GameManager::GameState::Singleplayer:
	{
		auto uiElements = Player::CreateUI(infoFont, 1, leftUiX, uiY);
		for (auto& element : uiElements)
		{
			level.push_back(std::move(element));
		}

		const glm::vec2 spawnPosition = GetPlayerSpawnPosition(levelLayout.playerSpawns.playerOne);
		auto player = Player::Create(1, spawnPosition.x, spawnPosition.y, SDLK_A, SDLK_D, SDLK_W, SDLK_S, SDLK_Q, SDLK_E);
		level.push_back(std::move(player));
		break;
	}
	case GameManager::GameState::Coop:
	{
		auto uiElements1 = Player::CreateUI(infoFont, 1, leftUiX, uiY);
		for (auto& element : uiElements1)
		{
			level.push_back(std::move(element));
		}

		const glm::vec2 playerOneSpawn = GetPlayerSpawnPosition(levelLayout.playerSpawns.playerOne);
		auto player1 = Player::Create(1, playerOneSpawn.x, playerOneSpawn.y, SDLK_A, SDLK_D, SDLK_W, SDLK_S, SDLK_Q, SDLK_E);
		level.push_back(std::move(player1));

		auto uiElements2 = Player::CreateUI(infoFont, 2, rightUiX, uiY);
		for (auto& element : uiElements2)
		{
			level.push_back(std::move(element));
		}

		const glm::vec2 playerTwoSpawn = GetPlayerSpawnPosition(levelLayout.playerSpawns.playerTwo);
		auto player2 = Player::Create(2, playerTwoSpawn.x, playerTwoSpawn.y, 0);
		level.push_back(std::move(player2));
		break;
	}
	case GameManager::GameState::Versus:
	{
		auto uiElements1 = Player::CreateUI(infoFont, 1, leftUiX, uiY);
		for (auto& element : uiElements1)
		{
			level.push_back(std::move(element));
		}

		const glm::vec2 playerOneSpawn = GetPlayerSpawnPosition(levelLayout.playerSpawns.playerOne);
		auto player1 = Player::Create(1, playerOneSpawn.x, playerOneSpawn.y, SDLK_A, SDLK_D, SDLK_W, SDLK_S, SDLK_Q, SDLK_E);
		level.push_back(std::move(player1));

		auto uiElements2 = Player::CreateUI(infoFont, 2, rightUiX, uiY);
		for (auto& element : uiElements2)
		{
			level.push_back(std::move(element));
		}

		const glm::vec2 versusSpawn = GetPlayerSpawnPosition(levelLayout.playerSpawns.versusEnemy);
		auto versusActor = Player::Create(2, versusSpawn.x, versusSpawn.y, 0);
		level.push_back(std::move(versusActor));
		break;
	}
	default:
		break;
	}

	return level;
}

std::unique_ptr<dae::GameObject> Level::CreateTextObject(const std::string& text,
	const std::shared_ptr<dae::Font>& font, float x, float y, const SDL_Color& color)
{
	auto gameObject = std::make_unique<dae::GameObject>();
	auto textComponent = std::make_unique<dae::TextComponent>(text, font, gameObject.get());
	textComponent->SetColor(color);
	gameObject->AddComponent(std::move(textComponent));
	gameObject->SetLocalPosition(x, y);
	return gameObject;
}

std::string Level::GetBackgroundTexture(int levelNumber)
{
	return "level" + std::to_string(levelNumber) + ".png";
}