#pragma once
#include "Command.h"
#include "GameObject.h"

class MoveCommand : public dae::Command
{
public:
	MoveCommand(dae::GameObject* pGameObject, float speed, bool moveHorizontally)
		: m_pGameObject(pGameObject), m_Speed(speed), m_MoveHorizontally(moveHorizontally){
	}
	void Execute() override;

private:
	dae::GameObject* m_pGameObject;
	float m_Speed;
	bool m_MoveHorizontally;
};