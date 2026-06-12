#include "EnemySpriteAnimatorComponent.h"
#include "GameObject.h"
#include "SpriteComponent.h"

#include <cmath>

EnemySpriteAnimatorComponent::EnemySpriteAnimatorComponent(dae::GameObject* pOwner)
	: BaseComponent(pOwner)
{
}

void EnemySpriteAnimatorComponent::Update()
{
	auto* pSpriteComponent = GetOwner()->GetComponent<dae::SpriteComponent>();
	if (pSpriteComponent == nullptr)
	{
		return;
	}

	const glm::vec3 currentPosition = GetOwner()->GetPosition();

	if (!m_isInitialized)
	{
		m_previousPosition = currentPosition;
		m_isInitialized = true;
		pSpriteComponent->SetFlipHorizontal(false);
		return;
	}

	const glm::vec3 delta = currentPosition - m_previousPosition;

	if (delta.x < -m_moveEpsilon)
	{
		m_facing = BurgerTimeSprites::Facing::Left;
	}
	else if (delta.x > m_moveEpsilon)
	{
		m_facing = BurgerTimeSprites::Facing::Right;
	}

	pSpriteComponent->SetFlipHorizontal(m_facing == BurgerTimeSprites::Facing::Right);
	m_previousPosition = currentPosition;
}

void EnemySpriteAnimatorComponent::Render() const
{
}