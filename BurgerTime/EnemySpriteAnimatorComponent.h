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
	BurgerTimeSprites::Facing m_facing{ BurgerTimeSprites::Facing::Left };

	const float MOVE_EPSILON{ 0.01f };
};