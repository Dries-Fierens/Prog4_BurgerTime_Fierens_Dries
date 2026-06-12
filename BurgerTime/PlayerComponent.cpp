#include "PlayerComponent.h"
#include "EventQueue.h"
#include "GameObject.h"
#include "Timer.h"

dae::PlayerComponent::PlayerComponent(int playerIndex, int lives, const glm::vec3& spawnPosition, GameObject* pOwner)
	: BaseComponent(pOwner)
	, m_playerIndex(playerIndex)
	, m_lives(lives)
	, m_score(0)
	, m_spawnPosition(spawnPosition)
{
}

void dae::PlayerComponent::Update()
{
	if (m_invulnerabilityTimer > 0.f)
	{
		m_invulnerabilityTimer -= dae::Timer::GetInstance().GetDeltaTime();
		if (m_invulnerabilityTimer < 0.f)
		{
			m_invulnerabilityTimer = 0.f;
		}
	}

	if (m_deathPauseTimer > 0.f)
	{
		m_deathPauseTimer -= dae::Timer::GetInstance().GetDeltaTime();
		if (m_deathPauseTimer < 0.f)
		{
			m_deathPauseTimer = 0.f;
		}
	}
}

void dae::PlayerComponent::Render() const
{
}

void dae::PlayerComponent::LoseLife()
{
	if (m_lives <= 0)
	{
		return;
	}

	--m_lives;

	Event event{};
	event.name = "PlayerDied";
	event.playerIndex = m_playerIndex;
	event.value = m_lives;
	EventQueue::GetInstance().SendEvent(event);
}

void dae::PlayerComponent::AddScore(int amount)
{
	m_score += amount;

	Event event{};
	event.name = "ScoreChanged";
	event.playerIndex = m_playerIndex;
	event.value = m_score;
	EventQueue::GetInstance().SendEvent(event);
}

bool dae::PlayerComponent::HandleEnemyHit()
{
	if (!CanBeHit())
	{
		return false;
	}

	LoseLife();

	if (m_lives > 0 && GetOwner() != nullptr)
	{
		GetOwner()->SetLocalPosition(m_spawnPosition);
		m_deathPauseTimer = DEATH_PAUSE_DURATION;
		m_invulnerabilityTimer = INVULNERABILITY_DURATION;
	}

	return true;
}