#include "HighScoreScene.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "TextComponent.h"
#include "GameManager.h"
#include "Renderer.h"
#include <string>

void HighScoreScene::Create()
{
	dae::Scene* currentScene = dae::SceneManager::GetInstance().GetCurrentScene();
	if (currentScene)
	{
		currentScene->RemoveAll();
		currentScene->SetName("High Scores");
	}
	else {
		currentScene = &dae::SceneManager::GetInstance().CreateScene("High Scores");
	}

	dae::SceneManager::GetInstance().SetCurrentScene(currentScene);

	auto fontNES = dae::ResourceManager::GetInstance().LoadFont("../Data/Pixel_NES.otf", 32);
	auto windowSize = dae::Renderer::GetInstance().GetWindowSize();

	auto titleObject = std::make_unique<dae::GameObject>();
	auto titleText = std::make_unique<dae::TextComponent>("HIGH SCORES", fontNES, titleObject.get());
	titleText->Update();
	auto titleSize = titleText->GetSize();
	titleObject->SetLocalPosition(windowSize.x / 2 - titleSize.x / 2, 50.f);
	titleObject->AddComponent(std::move(titleText));
	currentScene->Add(std::move(titleObject));

	const auto& playerScores = GameManager::GetInstance().GetPlayerScores();

	for (size_t i{}; i < playerScores.size(); ++i)
	{
		auto scoreObject = std::make_unique<dae::GameObject>();
		auto scoreText = std::make_unique<dae::TextComponent>(
			"P" + std::to_string(i + 1) + " Score: " + std::to_string(playerScores[i]),
			fontNES,
			scoreObject.get());

		scoreText->Update();
		auto scoreSize = scoreText->GetSize();
		scoreObject->SetLocalPosition(windowSize.x / 2 - scoreSize.x / 2, 140.f + static_cast<float>(i) * 60.f);
		scoreObject->AddComponent(std::move(scoreText));
		currentScene->Add(std::move(scoreObject));
	}
}