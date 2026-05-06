#include "StartSingleplayerCommand.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Level.h"
#include "GameManager.h"
#include "InputManager.h"
#include "Locator.h"
#include "MuteCommand.h"

void StartSingleplayerCommand::Execute()
{
	dae::Scene* currentScene = dae::SceneManager::GetInstance().GetCurrentScene();

	dae::InputManager::GetInstance().RemoveInputs();
	dae::InputManager::GetInstance().AddKeyboardCommand(std::make_unique<MuteCommand>(), SDLK_F2, dae::InputManager::InputType::OnDown);

	currentScene->RemoveAll();
	currentScene->SetName("Level 1");
	GameManager::GetInstance().SetGameState(GameManager::GameState::Singleplayer);
	for (auto& gameObject : Level::Create(1)) currentScene->Add(std::move(gameObject));

	Locator::Shutdown();
	Locator::Initialize();
	Locator::GetAudio()->PlayMusic("../Data/Game Start.wav", 20, -1);
}
