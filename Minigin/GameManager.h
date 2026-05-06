#pragma once
#include "EventQueue.h"
#include "Singleton.h"

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
	void SkipLevel();
	void SetGameState(GameState state) { m_gameState = state; }
	GameState GetGameState() const { return m_gameState; }
	int GetCurrentLevel() const { return m_currentLevel; }

private:
	friend class Singleton<GameManager>;
	GameManager() = default;

	GameState m_gameState{ GameState::Menu };
	int m_currentLevel{};
	int m_totalLevels{ 3 };
};