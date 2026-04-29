#include "AddScoreCommand.h"
#include "PlayerComponent.h"
#include "Locator.h"

void AddScoreCommand::Execute()
{
	//Locator::GetAudio()->PlaySound("Bonus Obtained.wav", 100, 0);

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