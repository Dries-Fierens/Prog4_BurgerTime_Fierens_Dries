#include "DeathCommand.h"
#include "PlayerComponent.h"

void DeathCommand::Execute()
{
	if (!m_pGameObject)
	{
		return;
	}

	const auto playerComponent = m_pGameObject->GetComponent<dae::PlayerComponent>();
	if (playerComponent)
	{
		playerComponent->LoseLife();
	}
}