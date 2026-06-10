#include "DeathCommand.h"
#include "PlayerComponent.h"
#include "Locator.h"

void DeathCommand::Execute()
{
#ifndef __EMSCRIPTEN__
	Locator::GetAudio()->PlaySound("Death.wav", 30, 0);
#endif

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