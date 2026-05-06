#include "Level.h"
#include "Scene.h"
#include "RenderComponent.h"
#include "ResourceManager.h"
#include "TextComponent.h"
#include "FPSCounter.h"
#include "GameManager.h"
#include "SceneManager.h"
#include "Player.h"

std::vector<std::unique_ptr<dae::GameObject>> Level::Create(int /*levelNumber*/)
{
	std::vector<std::unique_ptr<dae::GameObject>> level;

	auto go = std::make_unique<dae::GameObject>();
	auto background = std::make_unique<dae::RenderComponent>("background.png", go.get());
	go->AddComponent(std::move(background));
	level.push_back(std::move(go));

	go = std::make_unique<dae::GameObject>();
	auto logoDAE = std::make_unique<dae::RenderComponent>("logo.png", go.get());
	go->AddComponent(std::move(logoDAE));
	go->SetLocalPosition(358, 180);
	level.push_back(std::move(go));

	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

	go = std::make_unique<dae::GameObject>();
	auto text = std::make_unique<dae::TextComponent>("Programming 4 Assignment", font, go.get());
	text->SetColor({ 255, 255, 0, 255 });
	go->AddComponent(std::move(text));
	go->SetLocalPosition(292, 20);
	level.push_back(std::move(go));

	go = std::make_unique<dae::GameObject>();
	auto fpsComponent = std::make_unique<dae::FPSCounter>(font, go.get());
	go->AddComponent(std::move(fpsComponent));
	go->SetLocalPosition(10, 10);
	level.push_back(std::move(go));

	if (GameManager::GetInstance().GetGameState() == GameManager::GameState::Singleplayer)
	{
		auto uiElements1 = Player::CreateUI(font, 1, 10.f, 60.f);
		for (auto& element : uiElements1)
		{
			level.push_back(std::move(element));
		}
		auto player1 = Player::Create(1, 280.f, 280.f, 'a', 'd', 'w', 's', 'q', 'e');
		level.push_back(std::move(player1));
	}
	else 
	{
		auto uiElements1 = Player::CreateUI(font, 1, 10.f, 60.f);
		for (auto& element : uiElements1)
		{
			level.push_back(std::move(element));
		}
		auto player1 = Player::Create(1, 280.f, 280.f, 'a', 'd', 'w', 's', 'q', 'e');
		level.push_back(std::move(player1));

		auto uiElements2 = Player::CreateUI(font, 2, 720.f, 60.f);
		for (auto& element : uiElements2)
		{
			level.push_back(std::move(element));
		}
		auto player2 = Player::Create(2, 640.f, 280.f, 0);
		level.push_back(std::move(player2));
	}

	return level;
}
