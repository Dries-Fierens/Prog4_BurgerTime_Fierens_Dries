#include "MoveCommand.h"
#include "Timer.h"
#include "ColliderComponent.h"

void MoveCommand::Execute()
{
	if (m_pGameObject == nullptr)
	{
		return;
	}

	glm::vec3 newPosition = m_pGameObject->GetPosition();
	const glm::vec3 oldPosition = newPosition;

	if (m_MoveHorizontally)
	{
		newPosition.x += m_Speed * dae::Timer::GetInstance().GetDeltaTime();
	}
	else
	{
		newPosition.y += m_Speed * dae::Timer::GetInstance().GetDeltaTime();
	}

	m_pGameObject->SetLocalPosition(newPosition);

	const auto* pCollider = m_pGameObject->GetComponent<dae::ColliderComponent>();
	if (pCollider != nullptr && pCollider->IsOverlapping())
	{
		m_pGameObject->SetLocalPosition(oldPosition);
	}
}