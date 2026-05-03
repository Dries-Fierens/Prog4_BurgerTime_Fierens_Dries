#pragma once
#include "BaseComponent.h"
#include <vector>

namespace dae
{
	class ColliderComponent final : public BaseComponent
	{
	public:
		struct Rectf
		{
			float x{};
			float y{};
			float width{};
			float height{};
		};

		ColliderComponent(float width, float height, GameObject* pOwner);
		~ColliderComponent() override;

		void Update() override;
		void Render() const override;

		Rectf GetBounds() const;
		bool IsOverlapping() const;
		bool IsOverlapping(const ColliderComponent& other) const;

	private:
		float m_width{};
		float m_height{};

		static std::vector<ColliderComponent*> m_colliders;
	};
}