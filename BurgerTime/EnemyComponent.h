#pragma once
#include "BaseComponent.h"
#include "LevelData.h"
#include <glm/vec3.hpp>

class EnemyComponent final : public dae::BaseComponent
{
public:
	EnemyComponent(EnemyType type, dae::GameObject* pOwner);

	void Update() override;
	void Render() const override;

	EnemyType GetType() const { return m_type; }

private:
	bool HasMoved(const glm::vec3& from, const glm::vec3& to)
	{
		return std::abs(from.x - to.x) > MOVEMENT_EPSILON || std::abs(from.y - to.y) > MOVEMENT_EPSILON;
	}

	EnemyType m_type{};
	float m_speed{};
	float m_contactTimer{};

	const float ENEMY_WIDTH{ 32.f };
	const float ENEMY_HEIGHT{ 32.f };
	const float CONTACT_DAMAGE_COOLDOWN{ 0.25f };
	const float SAME_LEVEL_TOLERANCE{ 10.f };
	const float LADDER_APPROACH_THRESHOLD{ 8.f };
	const float MOVEMENT_EPSILON{ 0.001f };
};