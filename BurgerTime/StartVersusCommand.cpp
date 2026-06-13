#include "StartVersusCommand.h"
#include "Scene.h"
#include "SceneManager.h"
#include "Level.h"
#include "GameManager.h"
#include "InputManager.h"
#include "Locator.h"
#include "MuteCommand.h"
#include "ToggleDebugCommand.h"

void StartVersusCommand::Execute()
{
	dae::Scene* currentScene = dae::SceneManager::GetInstance().GetCurrentScene();

	dae::InputManager::GetInstance().RemoveInputs();
	dae::InputManager::GetInstance().AddKeyboardCommand(std::make_unique<MuteCommand>(), SDLK_F2, dae::InputManager::InputType::OnDown);
	dae::InputManager::GetInstance().AddKeyboardCommand(std::make_unique<ToggleDebugCommand>(), SDLK_F3, dae::InputManager::InputType::OnDown);

	currentScene->RemoveAll();
	currentScene->SetName("Level 1");
	GameManager::GetInstance().SetGameState(GameManager::GameState::Versus);
	for (auto& gameObject : Level::Create(1)) currentScene->Add(std::move(gameObject));

	Locator::Shutdown();
	Locator::Initialize();
	Locator::GetAudio()->PlayMusic("Game Start.wav", 5, -1);
}

