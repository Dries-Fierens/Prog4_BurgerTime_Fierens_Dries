#pragma once
#include "Command.h"
#include "GameObject.h"

class AddScoreCommand final : public dae::Command
{
public:
	AddScoreCommand(dae::GameObject* pGameObject, int amount)
		: m_pGameObject(pGameObject)
		, m_amount(amount)
	{
	}

	void Execute() override;

private:
	dae::GameObject* m_pGameObject{};
	int m_amount{};
};