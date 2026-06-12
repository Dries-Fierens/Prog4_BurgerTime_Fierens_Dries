#pragma once
#include "BaseComponent.h"
#include <glm/vec3.hpp>

namespace dae
{
	class PlayerComponent final : public BaseComponent
	{
	public:
		PlayerComponent(int playerIndex, int lives, const glm::vec3& spawnPosition, GameObject* pOwner);

		void Update() override;
		void Render() const override;

		void LoseLife();
		void AddScore(int amount);
		bool HandleEnemyHit();

		int GetPlayerIndex() const { return m_playerIndex; }
		int GetLives() const { return m_lives; }
		int GetScore() const { return m_score; }
		bool CanBeHit() const { return m_invulnerabilityTimer <= 0.f && m_lives > 0; }
		bool CanMove() const { return m_deathPauseTimer <= 0.f && m_lives > 0; }
		bool IsInvulnerable() const { return m_invulnerabilityTimer > 0.f; }
		float GetInvulnerabilityTimer() const { return m_invulnerabilityTimer; }

	private:
		int m_playerIndex{};
		int m_lives{};
		int m_score{};
		float m_invulnerabilityTimer{};
		float m_deathPauseTimer{};
		glm::vec3 m_spawnPosition{};

		const float INVULNERABILITY_DURATION{ 1.5f };
		const float DEATH_PAUSE_DURATION{ 0.35f };
	};
}