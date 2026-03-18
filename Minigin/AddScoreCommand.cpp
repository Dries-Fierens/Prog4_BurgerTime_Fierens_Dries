#include "AddScoreCommand.h"
#include "PlayerComponent.h"

void AddScoreCommand::Execute()
{
	if (!m_pGameObject)
	{
		return;
	}

	const auto playerComponent = m_pGameObject->GetComponent<dae::PlayerComponent>();
	if (playerComponent)
	{
		playerComponent->AddScore(m_amount);
	}
}