#pragma once
#include "EventQueue.h"
#include "Singleton.h"
#include <vector>

class GameManager final : public dae::Singleton<GameManager>, public EventListener
{
public:
	enum class GameState
	{
		Menu,
		Singleplayer,
		Coop,
		Versus,
		HighScore
	};

	~GameManager() override = default;
	GameManager(const GameManager& other) = delete;
	GameManager operator=(const GameManager& rhs) = delete;
	GameManager(GameManager&& other) = delete;
	GameManager operator=(GameManager&& rhs) = delete;

	void OnEvent(const Event& e) override;

	void Initialize();
	void SetLevel();
	void SetGameState(GameState state);
	GameState GetGameState() const { return m_gameState; }
	int GetCurrentLevel() const { return m_currentLevel; }
	const std::vector<int>& GetPlayerScores() const { return m_playerScores; }

private:
	friend class Singleton<GameManager>;
	GameManager() = default;

	void SetPlayerScore(int playerIndex, int score);

	GameState m_gameState{ GameState::Menu };
	int m_currentLevel{};
	int m_totalLevels{ 3 };
	std::vector<int> m_playerScores{};
};