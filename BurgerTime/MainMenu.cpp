#include "MainMenu.h"
#include "SceneManager.h"
#include "Scene.h"
#include "InputManager.h"
#include "GameObject.h"
#include "RenderComponent.h"
#include "ResourceManager.h"
#include "TextComponent.h"
#include "FPSCounter.h"
#include "StartSingleplayerCommand.h"
#include "StartCoopCommand.h"
#include "StartVersusCommand.h"
#include "MuteCommand.h"
#include "Locator.h"
#include <glm/glm.hpp>
#include "Renderer.h"

void MainMenu::Create()
{
	Locator::GetAudio()->PlayMusic("Data/BGM.wav", 20, 1);

	dae::Scene* currentScene = dae::SceneManager::GetInstance().GetCurrentScene();

	if (currentScene)
	{
		currentScene->RemoveAll();
		currentScene->SetName("Main Menu");
	}
	else {
		currentScene = &dae::SceneManager::GetInstance().CreateScene("Main Menu");
	}
	dae::SceneManager::GetInstance().SetCurrentScene(currentScene);

	dae::InputManager::GetInstance().RemoveInputs();
	dae::InputManager::GetInstance().AddKeyboardCommand(std::make_unique<StartSingleplayerCommand>(), '1', dae::InputManager::InputType::OnDown);
	dae::InputManager::GetInstance().AddKeyboardCommand(std::make_unique<StartCoopCommand>(), '2', dae::InputManager::InputType::OnDown);
	dae::InputManager::GetInstance().AddKeyboardCommand(std::make_unique<StartVersusCommand>(), '3', dae::InputManager::InputType::OnDown);
	dae::InputManager::GetInstance().AddKeyboardCommand(std::make_unique<MuteCommand>(), SDLK_F2, dae::InputManager::InputType::OnDown);

	glm::vec2 windowSize = dae::Renderer::GetInstance().GetWindowSize();

	auto go = std::make_unique<dae::GameObject>();
	auto logoBurgerTime = std::make_unique<dae::RenderComponent>("../Data/game_logo.png", go.get());
	auto logoSize = logoBurgerTime->GetSize();
	go->AddComponent(std::move(logoBurgerTime));
	go->SetLocalPosition(windowSize.x / 2 - logoSize.x / 2, 50);
	currentScene->Add(std::move(go));

	auto fontNES = dae::ResourceManager::GetInstance().LoadFont("../Data/Pixel_NES.otf", 32);

	auto singleplayer = std::make_unique<dae::GameObject>();
	auto singleplayerText = std::make_unique<dae::TextComponent>("PRESS 1 FOR SINGLEPLAYER", fontNES, singleplayer.get());
	singleplayerText->Update();
	auto singleplayerSize = singleplayerText->GetSize();
	singleplayer->SetLocalPosition(windowSize.x / 2 - singleplayerSize.x / 2, 320);
	singleplayer->AddComponent(std::move(singleplayerText));
	currentScene->Add(std::move(singleplayer));

	auto coop = std::make_unique<dae::GameObject>();
	auto coopText = std::make_unique<dae::TextComponent>("PRESS 2 FOR CO-OP", fontNES, coop.get());
	coopText->Update();
	auto coopSize = coopText->GetSize();
	coop->SetLocalPosition(windowSize.x / 2 - coopSize.x / 2, 390);
	coop->AddComponent(std::move(coopText));
	currentScene->Add(std::move(coop));

	auto versus = std::make_unique<dae::GameObject>();
	auto versusText = std::make_unique<dae::TextComponent>("PRESS 3 FOR VERSUS", fontNES, versus.get());
	versusText->Update();
	auto versusSize = versusText->GetSize();
	versus->SetLocalPosition(windowSize.x / 2 - versusSize.x / 2, 460);
	versus->AddComponent(std::move(versusText));
	currentScene->Add(std::move(versus));
}