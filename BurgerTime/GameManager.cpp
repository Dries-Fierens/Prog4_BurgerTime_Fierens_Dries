#include "GameManager.h"
#include "Audio.h"
#include "GameObject.h"
#include "HighScoreScene.h"
#include "InputManager.h"
#include "Level.h"
#include "Locator.h"
#include "MainMenu.h"
#include "MuteCommand.h"
#include "PlayerComponent.h"
#include "Scene.h"
#include "SceneManager.h"

void GameManager::OnEvent(const Event& e)
{
	if (e.name == "ScoreChanged")
	{
		SetPlayerScore(e.playerIndex, e.value);
		return;
	}

	if (e.name == "NextLevel")
	{
		SetLevel();
		return;
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
	if (m_gameState != GameState::Singleplayer &&
		m_gameState != GameState::Coop &&
		m_gameState != GameState::Versus)
	{
		return;
	}

	auto* currentScene = dae::SceneManager::GetInstance().GetCurrentScene();
	if (currentScene == nullptr)
	{
		return;
	}

	++m_currentLevel;
	if (m_currentLevel > m_totalLevels)
	{
		m_currentLevel = 1;
	}

	dae::InputManager::GetInstance().RemoveInputs();
	dae::InputManager::GetInstance().AddKeyboardCommand(
		std::make_unique<MuteCommand>(), SDLK_F2, dae::InputManager::InputType::OnDown);

	currentScene->RemoveAll();
	currentScene->SetName("Level " + std::to_string(m_currentLevel));

	for (auto& gameObject : Level::Create(m_currentLevel))
	{
		currentScene->Add(std::move(gameObject));
	}

	dae::SceneManager::GetInstance().SetCurrentScene(currentScene);
}