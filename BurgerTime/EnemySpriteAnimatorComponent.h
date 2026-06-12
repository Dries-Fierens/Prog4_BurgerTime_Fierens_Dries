#pragma once
#include "BaseComponent.h"
#include "SpriteData.h"
#include <glm/vec3.hpp>

class EnemySpriteAnimatorComponent final : public dae::BaseComponent
{
public:
	explicit EnemySpriteAnimatorComponent(dae::GameObject* pOwner);

	void Update() override;
	void Render() const override;

private:
	glm::vec3 m_previousPosition{};
	bool m_isInitialized{};
	BurgerTimeSprites::Facing m_facing{ BurgerTimeSprites::Facing::Left };

	const float m_moveEpsilon{ 0.01f };
};