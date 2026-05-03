#include "ColliderComponent.h"
#include "GameObject.h"
#include <algorithm>

std::vector<dae::ColliderComponent*> dae::ColliderComponent::m_colliders{};

dae::ColliderComponent::ColliderComponent(float width, float height, GameObject* pOwner)
	: m_width(width)
	, m_height(height)
	, BaseComponent(pOwner)
{
	m_colliders.emplace_back(this);
}

dae::ColliderComponent::~ColliderComponent()
{
	m_colliders.erase(std::remove(m_colliders.begin(), m_colliders.end(), this), m_colliders.end());
}

void dae::ColliderComponent::Update()
{
}

void dae::ColliderComponent::Render() const
{
}

dae::ColliderComponent::Rectf dae::ColliderComponent::GetBounds() const
{
	const auto position = GetOwner()->GetPosition();
	return { position.x, position.y, m_width, m_height };
}

bool dae::ColliderComponent::IsOverlapping() const
{
	for (const auto* pCollider : m_colliders)
	{
		if (pCollider == nullptr || pCollider == this)
		{
			continue;
		}

		if (IsOverlapping(*pCollider))
		{
			return true;
		}
	}

	return false;
}

bool dae::ColliderComponent::IsOverlapping(const ColliderComponent& other) const
{
	const auto a = GetBounds();
	const auto b = other.GetBounds();

	return a.x < b.x + b.width &&
		a.x + a.width > b.x &&
		a.y < b.y + b.height &&
		a.y + a.height > b.y;
}