#include "Player.h"
#include "GameObject.h"
#include "InputManager.h"
#include "Controller.h"
#include "PlayerComponent.h"
#include "RenderComponent.h"
#include "MoveCommand.h"
#include "DeathCommand.h"
#include "AddScoreCommand.h"
#include "LivesDisplayComponent.h"
#include "ScoreDisplayComponent.h"

constexpr int StartingLives{ 3 };
constexpr int ScorePerPickup{ 100 };
constexpr float PlayerMoveSpeed{ 200.f };

void Player::Create(dae::Scene& scene, int playerIndex, float x, float y,
	SDL_Keycode left, SDL_Keycode right, SDL_Keycode up, SDL_Keycode down,
	SDL_Keycode dieKey, SDL_Keycode scoreKey)
{
	auto playerObject = std::make_unique<dae::GameObject>();
	auto* playerPtr = playerObject.get();

	playerObject->SetLocalPosition(x, y);
	playerObject->AddComponent(std::make_unique<dae::RenderComponent>("icon.png", playerPtr));
	playerObject->AddComponent(std::make_unique<dae::PlayerComponent>(playerIndex, StartingLives, playerPtr));

	auto& input = dae::InputManager::GetInstance();
	input.AddKeyboardCommand(std::make_unique<MoveCommand>(playerPtr, -PlayerMoveSpeed, true), left, dae::InputManager::InputType::OnPressed);
	input.AddKeyboardCommand(std::make_unique<MoveCommand>(playerPtr, PlayerMoveSpeed, true), right, dae::InputManager::InputType::OnPressed);
	input.AddKeyboardCommand(std::make_unique<MoveCommand>(playerPtr, -PlayerMoveSpeed, false), up, dae::InputManager::InputType::OnPressed);
	input.AddKeyboardCommand(std::make_unique<MoveCommand>(playerPtr, PlayerMoveSpeed, false), down, dae::InputManager::InputType::OnPressed);

	input.AddKeyboardCommand(std::make_unique<DeathCommand>(playerPtr), dieKey, dae::InputManager::InputType::OnDown);
	input.AddKeyboardCommand(std::make_unique<AddScoreCommand>(playerPtr, ScorePerPickup), scoreKey, dae::InputManager::InputType::OnDown);

	scene.Add(std::move(playerObject));
}

void Player::CreateUI(dae::Scene& scene, const std::shared_ptr<dae::Font>& font, 
	int playerIndex, float x, float y)
{
	auto livesObject = std::make_unique<dae::GameObject>();
	auto livesDisplay = std::make_unique<dae::LivesDisplayComponent>(playerIndex, StartingLives, font, livesObject.get());
	livesObject->AddComponent(std::move(livesDisplay));
	livesObject->SetLocalPosition(x, y);
	scene.Add(std::move(livesObject));

	auto scoreObject = std::make_unique<dae::GameObject>();
	auto scoreDisplay = std::make_unique<dae::ScoreDisplayComponent>(playerIndex, 0, font, scoreObject.get());
	scoreObject->AddComponent(std::move(scoreDisplay));
	scoreObject->SetLocalPosition(x, y + 36.f);
	scene.Add(std::move(scoreObject));
}