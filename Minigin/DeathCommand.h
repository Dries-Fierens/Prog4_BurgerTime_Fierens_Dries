#pragma once
#include "Command.h"
#include "GameObject.h"

class DeathCommand : public dae::Command
{
public:
	DeathCommand(dae::GameObject* pGameObject) : m_pGameObject(pGameObject) {}
	void Execute() override;

private:
	dae::GameObject* m_pGameObject;
};