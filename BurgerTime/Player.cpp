#include "Player.h"
#include "GameObject.h"
#include "InputManager.h"
#include "Controller.h"
#include "PlayerComponent.h"
#include "PlayerSpriteAnimatorComponent.h"
#include "SpriteData.h"
#include "SpriteComponent.h"
#include "ColliderComponent.h"
#include "BoardMoveCommand.h"
#include "DeathCommand.h"
#include "AddScoreCommand.h"
#include "LivesDisplayComponent.h"
#include "ScoreDisplayComponent.h"
#include "GameRules.h"

std::unique_ptr<dae::GameObject> Player::Create(int playerIndex, float x, float y,
	SDL_Keycode left, SDL_Keycode right, SDL_Keycode up, SDL_Keycode down,
	SDL_Keycode dieKey, SDL_Keycode scoreKey)
{
	auto playerObject = std::make_unique<dae::GameObject>();
	auto* playerPtr = playerObject.get();

	playerObject->SetLocalPosition(x, y);

	auto sprite = std::make_unique<dae::SpriteComponent>("sprites.png", playerPtr);
	sprite->SetSourceRect(BurgerTimeSprites::GetPlayerFrame(
		playerIndex, BurgerTimeSprites::Facing::Right, false, 0));
	sprite->SetSize(PlayerColliderWidth, PlayerColliderHeight);
	playerObject->AddComponent(std::move(sprite));

	playerObject->AddComponent(std::make_unique<PlayerSpriteAnimatorComponent>(playerIndex, playerPtr));
	playerObject->AddComponent(std::make_unique<dae::PlayerComponent>(playerIndex, BurgerTimeRules::StartingLives, playerPtr));
	playerObject->AddComponent(std::make_unique<dae::ColliderComponent>(PlayerColliderWidth, PlayerColliderHeight, playerPtr));

	auto& input = dae::InputManager::GetInstance();
	input.AddKeyboardCommand(std::make_unique<BoardMoveCommand>(playerPtr, -PlayerMoveSpeed, true, PlayerColliderWidth, PlayerColliderHeight), left, dae::InputManager::InputType::OnPressed);
	input.AddKeyboardCommand(std::make_unique<BoardMoveCommand>(playerPtr, PlayerMoveSpeed, true, PlayerColliderWidth, PlayerColliderHeight), right, dae::InputManager::InputType::OnPressed);
	input.AddKeyboardCommand(std::make_unique<BoardMoveCommand>(playerPtr, -PlayerMoveSpeed, false, PlayerColliderWidth, PlayerColliderHeight), up, dae::InputManager::InputType::OnPressed);
	input.AddKeyboardCommand(std::make_unique<BoardMoveCommand>(playerPtr, PlayerMoveSpeed, false, PlayerColliderWidth, PlayerColliderHeight), down, dae::InputManager::InputType::OnPressed);

	input.AddKeyboardCommand(std::make_unique<DeathCommand>(playerPtr), dieKey, dae::InputManager::InputType::OnDown);
	input.AddKeyboardCommand(std::make_unique<AddScoreCommand>(playerPtr, ScorePerPickup), scoreKey, dae::InputManager::InputType::OnDown);

	return playerObject;
}

std::unique_ptr<dae::GameObject> Player::Create(int playerIndex, float x, float y,
	unsigned int controllerIndex)
{
	auto playerObject = std::make_unique<dae::GameObject>();
	auto* playerPtr = playerObject.get();

	playerObject->SetLocalPosition(x, y);

	auto sprite = std::make_unique<dae::SpriteComponent>("sprites.png", playerPtr);
	sprite->SetSourceRect(BurgerTimeSprites::GetPlayerFrame(
		playerIndex, BurgerTimeSprites::Facing::Right, false, 0));
	sprite->SetSize(PlayerColliderWidth, PlayerColliderHeight);
	playerObject->AddComponent(std::move(sprite));

	playerObject->AddComponent(std::make_unique<PlayerSpriteAnimatorComponent>(playerIndex, playerPtr));
	playerObject->AddComponent(std::make_unique<dae::PlayerComponent>(playerIndex, BurgerTimeRules::StartingLives, playerPtr));
	playerObject->AddComponent(std::make_unique<dae::ColliderComponent>(PlayerColliderWidth, PlayerColliderHeight, playerPtr));

	auto& input = dae::InputManager::GetInstance();
	input.AddControllerCommand(std::make_unique<BoardMoveCommand>(playerPtr, -PlayerMoveSpeed, true, PlayerColliderWidth, PlayerColliderHeight),
		dae::Controller::ButtonState::Left, controllerIndex, dae::InputManager::InputType::OnPressed);
	input.AddControllerCommand(std::make_unique<BoardMoveCommand>(playerPtr, PlayerMoveSpeed, true, PlayerColliderWidth, PlayerColliderHeight),
		dae::Controller::ButtonState::Right, controllerIndex, dae::InputManager::InputType::OnPressed);
	input.AddControllerCommand(std::make_unique<BoardMoveCommand>(playerPtr, -PlayerMoveSpeed, false, PlayerColliderWidth, PlayerColliderHeight),
		dae::Controller::ButtonState::Up, controllerIndex, dae::InputManager::InputType::OnPressed);
	input.AddControllerCommand(std::make_unique<BoardMoveCommand>(playerPtr, PlayerMoveSpeed, false, PlayerColliderWidth, PlayerColliderHeight),
		dae::Controller::ButtonState::Down, controllerIndex, dae::InputManager::InputType::OnPressed);

	input.AddControllerCommand(std::make_unique<DeathCommand>(playerPtr),
		dae::Controller::ButtonState::A, controllerIndex, dae::InputManager::InputType::OnDown);
	input.AddControllerCommand(std::make_unique<AddScoreCommand>(playerPtr, ScorePerPickup),
		dae::Controller::ButtonState::B, controllerIndex, dae::InputManager::InputType::OnDown);

	return playerObject;
}

std::vector<std::unique_ptr<dae::GameObject>> Player::CreateUI(const std::shared_ptr<dae::Font>& font,
	int playerIndex, float x, float y)
{
	std::vector<std::unique_ptr<dae::GameObject>> uiElements;

	auto livesObject = std::make_unique<dae::GameObject>();
	auto livesDisplay = std::make_unique<dae::LivesDisplayComponent>(playerIndex, BurgerTimeRules::StartingLives, font, livesObject.get());
	livesObject->AddComponent(std::move(livesDisplay));
	livesObject->SetLocalPosition(x, y);
	uiElements.push_back(std::move(livesObject));

	auto scoreObject = std::make_unique<dae::GameObject>();
	auto scoreDisplay = std::make_unique<dae::ScoreDisplayComponent>(playerIndex, 0, font, scoreObject.get());
	scoreObject->AddComponent(std::move(scoreDisplay));
	scoreObject->SetLocalPosition(x, y + 36.f);
	uiElements.push_back(std::move(scoreObject));

	return uiElements;
}