#pragma once
#include "BaseComponent.h"

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

		int GetPlayerIndex() const { return m_playerIndex; }
		int GetLives() const { return m_lives; }
		int GetScore() const { return m_score; }

	private:
		int m_playerIndex{};
		int m_lives{};
		int m_score{};
	};
}