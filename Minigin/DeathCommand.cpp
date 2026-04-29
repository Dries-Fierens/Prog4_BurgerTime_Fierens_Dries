#include "DeathCommand.h"
#include "PlayerComponent.h"
#include "Locator.h"

void DeathCommand::Execute()
{
	//Locator::GetAudio()->PlaySound("Death.wav", 100, 0);

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