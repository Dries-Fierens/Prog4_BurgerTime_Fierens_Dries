#pragma once
#include "Command.h"
#include "GameObject.h"

class BoardMoveCommand final : public dae::Command
{
public:
	BoardMoveCommand(dae::GameObject* pGameObject, float speed, bool moveHorizontally,
		float actorWidth, float actorHeight);

	void Execute() override;

private:
	dae::GameObject* m_pGameObject{};
	float m_speed{};
	bool m_moveHorizontally{};
	float m_actorWidth{};
	float m_actorHeight{};
};