#include "GameManager.h"
#include "MainMenu.h"
#include "Scene.h"
#include "SceneManager.h"
#include "GameObject.h"
#include "PlayerComponent.h"
#include "Level.h"
#include "Locator.h"
#include "Audio.h"

void GameManager::OnEvent(const Event& e)
{
	//auto currentScene = dae::SceneManager::GetInstance().GetCurrentScene();

	if (e.name == "NextLevel")
	{
		bool goNextLevel = true;
		//for (const auto& go : currentScene->GetGameObjects())
		//{
		//	bool burgerComplete = go->HasComponent<dae::BurgerComponent>() && go->GetComponent<dae::BurgerComponent>()->IsComplete();
		//	goNextLevel = burgerComplete;
		//	break;
		//}

		if (goNextLevel) SkipLevel();
	}

	if (e.name == "PlayerDead")
	{
		Locator::Shutdown();
		Locator::Initialize();
		MainMenu::Create();
		m_gameState = GameState::Menu;
	}
}

void GameManager::Initialize()
{
	MainMenu::Create();

	dae::EventQueue::GetInstance().AddListener(this);
}

void GameManager::SkipLevel()
{
	if (m_gameState == GameState::Singleplayer ||
		m_gameState == GameState::Coop ||
		m_gameState == GameState::Versus)
	{
		auto currentScene = dae::SceneManager::GetInstance().GetCurrentScene();
		auto& gameObjects = currentScene->GetGameObjects();

		// Remove all game objects except players
		for (const auto& go : gameObjects)
		{
			if (!go->HasComponent<dae::PlayerComponent>()) currentScene->Remove(go.get());
		}

		auto sceneName = currentScene->GetName();
		char levelNumber = sceneName[sceneName.size() - 1];
		if (std::isdigit(levelNumber))
		{
			m_currentLevel = levelNumber - '0';

			if (m_currentLevel < m_totalLevels)
			{
				++m_currentLevel;
				currentScene->SetName("Level " + std::to_string(m_currentLevel));
				for (auto& gameObject : Level::Create(m_currentLevel)) currentScene->Add(std::move(gameObject));

				dae::SceneManager::GetInstance().SetCurrentScene(currentScene);
			}
			else
			{
				// create high score scene
				//m_gameState = GameState::HighScore;

				MainMenu::Create();
				m_gameState = GameState::Menu;
			}
		}
	}
}
