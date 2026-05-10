#include "GameManager.h"
#include "MainMenu.h"
#include "Scene.h"
#include "SceneManager.h"
#include "GameObject.h"
#include "PlayerComponent.h"
#include "Level.h"
#include "Locator.h"
#include "Audio.h"
#include "HighScoreScene.h"

void GameManager::OnEvent(const Event& e)
{
	if (e.name == "ScoreChanged")
	{
		SetPlayerScore(e.playerIndex, e.value);
		return;
	}

	if (e.name == "NextLevel")
	{
		bool goNextLevel = true;

		// Example for next level condition
		//for (const auto& go : currentScene->GetGameObjects())
		//{
		//	bool burgersComplete = go->HasComponent<dae::BurgerComponent>() && go->GetComponent<dae::BurgerComponent>()->IsComplete();
		//	goNextLevel = burgersComplete;
		//	break;
		//}

		if (goNextLevel) SetLevel();
	}

	if (e.name == "PlayerDied" && e.value <= 0)
	{
		Locator::Shutdown();
		Locator::Initialize();
		HighScoreScene::Create();
		m_gameState = GameState::HighScore;
	}
}

void GameManager::Initialize()
{
	MainMenu::Create();

	dae::EventQueue::GetInstance().AddListener(this);
}

void GameManager::SetGameState(GameState state)
{
	m_gameState = state;
	m_currentLevel = 1;

	switch (state)
	{
	case GameState::Singleplayer:
		m_playerScores.assign(1, 0);
		break;
	case GameState::Coop:
	case GameState::Versus:
		m_playerScores.assign(2, 0);
		break;
	default:
		break;
	}
}

void GameManager::SetPlayerScore(int playerIndex, int score)
{
	if (playerIndex <= 0)
	{
		return;
	}

	if (m_playerScores.size() < static_cast<size_t>(playerIndex))
	{
		m_playerScores.resize(static_cast<size_t>(playerIndex), 0);
	}

	m_playerScores[static_cast<size_t>(playerIndex) - 1] = score;
}

void GameManager::SetLevel()
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
				HighScoreScene::Create();
				m_gameState = GameState::HighScore;
			}
		}
	}
}