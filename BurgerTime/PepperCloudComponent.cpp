#include "PepperCloudComponent.h"
#include "EnemyComponent.h"
#include "GameObject.h"
#include "Scene.h"
#include "SceneManager.h"
#include "Timer.h"
#include <algorithm>

PepperCloudComponent::PepperCloudComponent(int playerIndex, dae::GameObject* pOwner)
	: BaseComponent(pOwner)
	, m_playerIndex(playerIndex)
{
}

void PepperCloudComponent::Update()
{
	if (m_hasExpired)
	{
		return;
	}

	m_lifeTime -= dae::Timer::GetInstance().GetDeltaTime();
	if (m_lifeTime <= 0.f)
	{
		m_hasExpired = true;
		return;
	}

	auto* pScene = dae::SceneManager::GetInstance().GetCurrentScene();
	if (pScene == nullptr)
	{
		return;
	}

	const glm::vec3 pepperPosition = GetOwner()->GetPosition();
	const float pepperLeft = pepperPosition.x;
	const float pepperRight = pepperPosition.x + 48.f;
	const float pepperTop = pepperPosition.y;
	const float pepperBottom = pepperPosition.y + 32.f;

	for (const auto& gameObject : pScene->GetGameObjects())
	{
		auto* pEnemyComponent = gameObject->GetComponent<EnemyComponent>();
		if (pEnemyComponent == nullptr)
		{
			continue;
		}

		const glm::vec3 enemyPosition = gameObject->GetPosition();
		const float enemyLeft = enemyPosition.x;
		const float enemyRight = enemyPosition.x + 32.f;
		const float enemyTop = enemyPosition.y;
		const float enemyBottom = enemyPosition.y + 32.f;

		const bool overlaps = pepperLeft < enemyRight &&
			pepperRight > enemyLeft &&
			pepperTop < enemyBottom &&
			pepperBottom > enemyTop;

		if (overlaps)
		{
			pEnemyComponent->Stun();
		}
	}
}

void PepperCloudComponent::Render() const
{
}