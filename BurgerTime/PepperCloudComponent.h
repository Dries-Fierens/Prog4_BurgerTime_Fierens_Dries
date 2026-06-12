#pragma once
#include "BaseComponent.h"

class PepperCloudComponent final : public dae::BaseComponent
{
public:
	explicit PepperCloudComponent(dae::GameObject* pOwner);

	void Update() override;
	void Render() const override;

private:
	float m_lifeTime{ 0.35f };
};