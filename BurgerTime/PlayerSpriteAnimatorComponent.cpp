#include "PlayerSpriteAnimatorComponent.h"
#include "GameObject.h"
#include "SpriteData.h"
#include "SpriteComponent.h"
#include "Timer.h"
#include <cmath>

PlayerSpriteAnimatorComponent::PlayerSpriteAnimatorComponent(int playerIndex, dae::GameObject* pOwner)
	: BaseComponent(pOwner)
	, m_playerIndex(playerIndex)
{
}

void PlayerSpriteAnimatorComponent::Update()
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
		pSpriteComponent->SetSourceRect(BurgerTimeSprites::GetPlayerFrame(
			m_playerIndex, BurgerTimeSprites::Facing::Right, false, 0));
		return;
	}

	const glm::vec3 delta = currentPosition - m_previousPosition;

	const bool isMovingHorizontally = std::abs(delta.x) > MOVE_EPSILON;
	const bool isMovingVertically = std::abs(delta.y) > MOVE_EPSILON;
	const bool isMoving = isMovingHorizontally || isMovingVertically;

	if (delta.x < -MOVE_EPSILON)
	{
		m_facing = BurgerTimeSprites::Facing::Left;
	}
	else if (delta.x > MOVE_EPSILON)
	{
		m_facing = BurgerTimeSprites::Facing::Right;
	}

	if (isMoving)
	{
		m_animationTimer += dae::Timer::GetInstance().GetDeltaTime();
	}
	else
	{
		m_animationTimer = 0.f;
	}

	const int animationFrame = static_cast<int>(m_animationTimer / ANIMATION_FRAME_TIME);
	pSpriteComponent->SetSourceRect(BurgerTimeSprites::GetPlayerFrame(
		m_playerIndex, m_facing, isMoving, animationFrame));

	m_previousPosition = currentPosition;
}

void PlayerSpriteAnimatorComponent::Render() const
{
}