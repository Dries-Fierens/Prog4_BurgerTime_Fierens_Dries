#pragma once
#include "BaseComponent.h"
#include <glm/vec3.hpp>

namespace dae
{
	class PlayerComponent final : public BaseComponent
	{
	public:
		PlayerComponent(int playerIndex, int lives, int pepperShots, int initialScore, const glm::vec3& spawnPosition, GameObject* pOwner);

		void Update() override;
		void Render() const override;

		void LoseLife();
		void AddScore(int amount);
		bool HandleEnemyHit();
		bool UsePepper();

		int GetPlayerIndex() const { return m_playerIndex; }
		int GetLives() const { return m_lives; }
		int GetScore() const { return m_score; }
		int GetPepperShots() const { return m_pepperShots; }

		bool CanBeHit() const { return m_invulnerabilityTimer <= 0.f && m_lives > 0; }
		bool CanMove() const { return m_deathPauseTimer <= 0.f && m_lives > 0; }
		bool IsInvulnerable() const { return m_invulnerabilityTimer > 0.f; }
		float GetInvulnerabilityTimer() const { return m_invulnerabilityTimer; }

		bool IsFacingRight() const { return m_isFacingRight; }
		void SetFacingRight(bool isFacingRight) { m_isFacingRight = isFacingRight; }

	private:
		int m_playerIndex{};
		int m_lives{};
		int m_score{};
		int m_pepperShots{};
		float m_invulnerabilityTimer{};
		float m_deathPauseTimer{};
		glm::vec3 m_spawnPosition{};
		bool m_isFacingRight{};

		const float INVULNERABILITY_DURATION{ 1.5f };
		const float DEATH_PAUSE_DURATION{ 0.35f };
	};
}