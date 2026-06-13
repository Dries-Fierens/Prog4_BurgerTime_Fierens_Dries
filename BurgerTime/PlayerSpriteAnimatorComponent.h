#pragma once
#include "BaseComponent.h"
#include <glm/vec3.hpp>
#include "SpriteData.h"

namespace dae
{
	class SpriteComponent;
}

class PlayerSpriteAnimatorComponent final : public dae::BaseComponent
{
public:
	PlayerSpriteAnimatorComponent(int playerIndex, dae::GameObject* pOwner);

	void Update() override;
	void Render() const override;

private:
	int m_playerIndex{};
	glm::vec3 m_previousPosition{};
	float m_animationTimer{};
	BurgerTimeSprites::Facing m_facing{ BurgerTimeSprites::Facing::Right };

	const float MOVE_EPSILON{ 0.01f };
	const float ANIMATION_FRAME_TIME{ 0.12f };
};