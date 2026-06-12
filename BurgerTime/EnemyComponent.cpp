#include "EnemyComponent.h"
#include "BoardComponent.h"
#include "ColliderComponent.h"
#include "GameObject.h"
#include "PlayerComponent.h"
#include "Scene.h"
#include "SceneManager.h"
#include "SpriteComponent.h"
#include "Timer.h"
#include <cmath>
#include <limits>

EnemyComponent::EnemyComponent(EnemyType type, const glm::vec3& spawnPosition, dae::GameObject* pOwner)
	: BaseComponent(pOwner)
	, m_type(type)
	, m_spawnPosition(spawnPosition)
{
	switch (m_type)
	{
	case EnemyType::HotDog:
		m_speed = 90.f;
		break;
	case EnemyType::Pickle:
		m_speed = 82.f;
		break;
	case EnemyType::Egg:
		m_speed = 98.f;
		break;
	default:
		m_speed = 90.f;
		break;
	}
}

void EnemyComponent::Update()
{
	const float deltaTime = dae::Timer::GetInstance().GetDeltaTime();

	if (m_contactTimer > 0.f)
	{
		m_contactTimer -= deltaTime;
		if (m_contactTimer < 0.f)
		{
			m_contactTimer = 0.f;
		}
	}

	auto* pSpriteComponent = GetOwner()->GetComponent<dae::SpriteComponent>();
	if (pSpriteComponent != nullptr)
	{
		pSpriteComponent->SetVisible(m_respawnTimer <= 0.f);
	}

	if (m_respawnTimer > 0.f)
	{
		m_respawnTimer -= deltaTime;
		if (m_respawnTimer < 0.f)
		{
			m_respawnTimer = 0.f;
		}
		return;
	}

	if (m_stunTimer > 0.f)
	{
		m_stunTimer -= deltaTime;
		if (m_stunTimer < 0.f)
		{
			m_stunTimer = 0.f;
		}
		return;
	}

	auto* pScene = dae::SceneManager::GetInstance().GetCurrentScene();
	if (pScene == nullptr)
	{
		return;
	}

	dae::GameObject* pTargetPlayerObject{};
	dae::PlayerComponent* pTargetPlayerComponent{};
	float closestDistanceSquared{ std::numeric_limits<float>::max() };

	for (const auto& gameObject : pScene->GetGameObjects())
	{
		auto* pPlayerComponent = gameObject->GetComponent<dae::PlayerComponent>();
		if (pPlayerComponent == nullptr || pPlayerComponent->GetLives() <= 0)
		{
			continue;
		}

		const glm::vec3 delta = gameObject->GetPosition() - GetOwner()->GetPosition();
		const float distanceSquared = delta.x * delta.x + delta.y * delta.y;

		if (distanceSquared < closestDistanceSquared)
		{
			closestDistanceSquared = distanceSquared;
			pTargetPlayerObject = gameObject.get();
			pTargetPlayerComponent = pPlayerComponent;
		}
	}

	if (pTargetPlayerObject == nullptr || pTargetPlayerComponent == nullptr)
	{
		return;
	}

	const glm::vec3 currentPosition = GetOwner()->GetPosition();
	const glm::vec3 targetPosition = pTargetPlayerObject->GetPosition();

	glm::vec3 nextPosition = currentPosition;
	const auto* pBoard = BoardComponent::GetActiveBoard();

	if (pBoard != nullptr)
	{
		const float currentFeetY = currentPosition.y + ENEMY_HEIGHT;
		const float targetFeetY = targetPosition.y + ENEMY_HEIGHT;
		const bool sameLevel = std::abs(currentFeetY - targetFeetY) <= SAME_LEVEL_TOLERANCE;

		if (sameLevel)
		{
			glm::vec3 horizontalAttempt = currentPosition;
			horizontalAttempt.x += (targetPosition.x < currentPosition.x ? -m_speed : m_speed) * deltaTime;

			nextPosition = pBoard->GetValidatedPosition(
				currentPosition, horizontalAttempt, ENEMY_WIDTH, ENEMY_HEIGHT, true);
		}
		else
		{
			float ladderX{};
			if (pBoard->TryGetBestLadderX(currentPosition, targetPosition, ENEMY_WIDTH, ENEMY_HEIGHT, ladderX))
			{
				const float currentCenterX = currentPosition.x + ENEMY_WIDTH * 0.5f;

				if (std::abs(currentCenterX - ladderX) > LADDER_APPROACH_THRESHOLD)
				{
					glm::vec3 horizontalAttempt = currentPosition;
					horizontalAttempt.x += (ladderX < currentCenterX ? -m_speed : m_speed) * deltaTime;

					nextPosition = pBoard->GetValidatedPosition(
						currentPosition, horizontalAttempt, ENEMY_WIDTH, ENEMY_HEIGHT, true);
				}
				else
				{
					glm::vec3 verticalAttempt = currentPosition;
					verticalAttempt.y += (targetPosition.y < currentPosition.y ? -m_speed : m_speed) * deltaTime;

					nextPosition = pBoard->GetValidatedPosition(
						currentPosition, verticalAttempt, ENEMY_WIDTH, ENEMY_HEIGHT, false);

					if (!HasMoved(currentPosition, nextPosition))
					{
						glm::vec3 horizontalAttempt = currentPosition;
						horizontalAttempt.x += (targetPosition.x < currentPosition.x ? -m_speed : m_speed) * deltaTime;

						nextPosition = pBoard->GetValidatedPosition(
							currentPosition, horizontalAttempt, ENEMY_WIDTH, ENEMY_HEIGHT, true);
					}
				}
			}
			else
			{
				glm::vec3 horizontalAttempt = currentPosition;
				horizontalAttempt.x += (targetPosition.x < currentPosition.x ? -m_speed : m_speed) * deltaTime;

				nextPosition = pBoard->GetValidatedPosition(
					currentPosition, horizontalAttempt, ENEMY_WIDTH, ENEMY_HEIGHT, true);
			}
		}
	}

	GetOwner()->SetLocalPosition(nextPosition);

	const auto* pEnemyCollider = GetOwner()->GetComponent<dae::ColliderComponent>();
	const auto* pPlayerCollider = pTargetPlayerObject->GetComponent<dae::ColliderComponent>();

	if (pEnemyCollider != nullptr &&
		pPlayerCollider != nullptr &&
		pEnemyCollider->IsOverlapping(*pPlayerCollider) &&
		m_contactTimer <= 0.f)
	{
		if (pTargetPlayerComponent->HandleEnemyHit())
		{
			Respawn();
			m_contactTimer = CONTACT_DAMAGE_COOLDOWN;
		}
	}
}

void EnemyComponent::Render() const
{
}

void EnemyComponent::Stun()
{
	if (IsRespawning())
	{
		return;
	}

	m_stunTimer = STUN_DURATION;
}

void EnemyComponent::Respawn()
{
	GetOwner()->SetLocalPosition(m_spawnPosition);
	m_respawnTimer = RESPAWN_DURATION;
	m_stunTimer = 0.f;
}