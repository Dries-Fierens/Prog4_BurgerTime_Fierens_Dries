#pragma once
#include "Command.h"
#include "GameObject.h"

class PepperCommand final : public dae::Command
{
public:
	explicit PepperCommand(dae::GameObject* pPlayer);

	void Execute() override;

private:
	dae::GameObject* m_pPlayer{};
};