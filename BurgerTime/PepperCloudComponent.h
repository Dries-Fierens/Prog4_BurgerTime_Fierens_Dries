#pragma once
#include "BaseComponent.h"

#include <vector>

class PepperCloudComponent final : public dae::BaseComponent
{
public:
	PepperCloudComponent(int playerIndex, dae::GameObject* pOwner);

	void Update() override;
	void Render() const override;

private:
	int m_playerIndex{};
	float m_lifeTime{ 0.35f };
	bool m_hasExpired{};
};