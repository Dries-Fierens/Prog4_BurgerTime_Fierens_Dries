#include "PepperCommand.h"
#include "GameObject.h"
#include "PepperCloudComponent.h"
#include "PlayerComponent.h"
#include "Scene.h"
#include "SceneManager.h"

PepperCommand::PepperCommand(dae::GameObject* pPlayer)
	: m_pPlayer(pPlayer)
{
}

void PepperCommand::Execute()
{
	if (m_pPlayer == nullptr)
	{
		return;
	}

	auto* pPlayerComponent = m_pPlayer->GetComponent<dae::PlayerComponent>();
	if (pPlayerComponent == nullptr || !pPlayerComponent->UsePepper())
	{
		return;
	}

	auto* pScene = dae::SceneManager::GetInstance().GetCurrentScene();
	if (pScene == nullptr)
	{
		return;
	}

	const glm::vec3 playerPosition = m_pPlayer->GetPosition();

	auto pepperObject = std::make_unique<dae::GameObject>();
	auto* pPepperObject = pepperObject.get();

	const bool isFacingRight = pPlayerComponent->IsFacingRight();
	const float offsetX = isFacingRight ? 28.f : -44.f;

	pepperObject->SetLocalPosition(playerPosition.x + offsetX, playerPosition.y);
	pepperObject->AddComponent(std::make_unique<PepperCloudComponent>(
		pPlayerComponent->GetPlayerIndex(),
		pPepperObject));

	pScene->Add(std::move(pepperObject));
}