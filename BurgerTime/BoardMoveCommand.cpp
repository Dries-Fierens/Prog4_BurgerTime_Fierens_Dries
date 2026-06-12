#include "BoardMoveCommand.h"
#include "BoardComponent.h"
#include "ColliderComponent.h"
#include "PlayerComponent.h"
#include "Timer.h"

BoardMoveCommand::BoardMoveCommand(dae::GameObject* pGameObject, float speed, bool moveHorizontally,
	float actorWidth, float actorHeight)
	: m_pGameObject(pGameObject)
	, m_speed(speed)
	, m_moveHorizontally(moveHorizontally)
	, m_actorWidth(actorWidth)
	, m_actorHeight(actorHeight)
{
}

void BoardMoveCommand::Execute()
{
	if (m_pGameObject == nullptr)
	{
		return;
	}

	const auto* pPlayerComponent = m_pGameObject->GetComponent<dae::PlayerComponent>();
	if (pPlayerComponent != nullptr && !pPlayerComponent->CanMove())
	{
		return;
	}

	glm::vec3 proposedPosition = m_pGameObject->GetPosition();
	const glm::vec3 originalPosition = proposedPosition;

	if (m_moveHorizontally)
	{
		proposedPosition.x += m_speed * dae::Timer::GetInstance().GetDeltaTime();
	}
	else
	{
		proposedPosition.y += m_speed * dae::Timer::GetInstance().GetDeltaTime();
	}

	const auto* pBoard = BoardComponent::GetActiveBoard();
	if (pBoard != nullptr)
	{
		proposedPosition = pBoard->GetValidatedPosition(originalPosition, proposedPosition,
			m_actorWidth, m_actorHeight, m_moveHorizontally);
	}

	m_pGameObject->SetLocalPosition(proposedPosition);

	const auto* pCollider = m_pGameObject->GetComponent<dae::ColliderComponent>();
	if (pCollider != nullptr && pCollider->IsOverlapping())
	{
		m_pGameObject->SetLocalPosition(originalPosition);
	}
}