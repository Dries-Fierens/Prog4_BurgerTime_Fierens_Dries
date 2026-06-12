#pragma once
#include "BaseComponent.h"
#include <glm/vec3.hpp>

namespace dae
{
	class PlayerComponent final : public BaseComponent
	{
	public:
		PlayerComponent(int playerIndex, int lives, GameObject* pOwner);

		void Update() override;
		void Render() const override;

		void LoseLife();
		void AddScore(int amount);
		void HandleEnemyHit();

		int GetPlayerIndex() const { return m_playerIndex; }
		int GetLives() const { return m_lives; }
		int GetScore() const { return m_score; }
		bool CanBeHit() const { return m_invulnerabilityTimer <= 0.f && m_lives > 0; }

	private:
		int m_playerIndex{};
		int m_lives{};
		int m_score{};
		float m_invulnerabilityTimer{};
		glm::vec3 m_spawnPosition{};

		const float INVULNERABILITY_DURATION{ 1.5f };
	};
}