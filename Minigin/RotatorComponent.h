#pragma once
#include "BaseComponent.h"
#include <glm/glm.hpp>

namespace dae
{
	class GameObject;
	class RotatorComponent final : public BaseComponent
	{
	public:
		RotatorComponent(float speed, float startAngle, float radius, GameObject* pOwner);
		~RotatorComponent() = default;
		RotatorComponent(const RotatorComponent& other) = delete;
		RotatorComponent(RotatorComponent&& other) noexcept = delete;
		RotatorComponent& operator=(const RotatorComponent& other) = delete;
		RotatorComponent& operator=(RotatorComponent&& other) noexcept = delete;

		void Update() override;
		void Render() const override {};

	private:
		glm::vec3 m_position;
		float m_angle{};
		float m_speed{};
		float m_radius{};

	};
}
