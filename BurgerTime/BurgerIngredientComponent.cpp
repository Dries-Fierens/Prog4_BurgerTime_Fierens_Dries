#include "BurgerIngredientComponent.h"
#include "GameObject.h"
#include "GameRules.h"
#include "PlayerComponent.h"
#include "Scene.h"
#include "SceneManager.h"
#include "TextComponent.h"
#include "Timer.h"
#include <SDL3/SDL.h>
#include <algorithm>
#include <cmath>

BurgerIngredientComponent::BurgerIngredientComponent(IngredientType type, float width,
	std::vector<float> dropStops, dae::GameObject* pOwner)
	: BaseComponent(pOwner)
	, m_type(type)
	, m_width(width)
	, m_dropStops(std::move(dropStops))
{
	RefreshDebugText();
}

void BurgerIngredientComponent::Update()
{
	if (m_isComplete)
	{
		return;
	}

	if (m_isDropping)
	{
		UpdateDrop();
		return;
	}

	UpdateWalkProgress();
}

void BurgerIngredientComponent::Render() const
{
}

void BurgerIngredientComponent::SetIngredientBelow(BurgerIngredientComponent* pIngredientBelow)
{
	m_pIngredientBelow = pIngredientBelow;
}

void BurgerIngredientComponent::ForceDrop(int playerIndex)
{
	if (m_isComplete || m_isDropping || m_nextDropIndex >= m_dropStops.size())
	{
		return;
	}

	m_lastTriggerPlayerIndex = playerIndex;
	m_isDropping = true;
}

void BurgerIngredientComponent::UpdateWalkProgress()
{
	auto* pScene = dae::SceneManager::GetInstance().GetCurrentScene();
	if (pScene == nullptr)
	{
		return;
	}

	const auto ingredientPosition = GetOwner()->GetPosition();
	const float segmentWidth = m_width / static_cast<float>(SEGMENT_COUNT);

	bool hasProgressChanged{};

	for (const auto& gameObject : pScene->GetGameObjects())
	{
		if (!gameObject->HasComponent<dae::PlayerComponent>())
		{
			continue;
		}

		auto* pPlayerComponent = gameObject->GetComponent<dae::PlayerComponent>();
		const auto playerPosition = gameObject->GetPosition();

		if (std::abs(playerPosition.y - ingredientPosition.y) > VERTICAL_OVERLAP_TOLERANCE)
		{
			continue;
		}

		const float playerCenterX = playerPosition.x + PLAYER_WIDTH * 0.5f;
		if (playerCenterX < ingredientPosition.x || playerCenterX > ingredientPosition.x + m_width)
		{
			continue;
		}

		int segmentIndex = static_cast<int>((playerCenterX - ingredientPosition.x) / segmentWidth);
		segmentIndex = std::clamp(segmentIndex, 0, SEGMENT_COUNT - 1);

		if (!m_walkedSegments[static_cast<size_t>(segmentIndex)])
		{
			m_walkedSegments[static_cast<size_t>(segmentIndex)] = true;
			m_lastTriggerPlayerIndex = pPlayerComponent->GetPlayerIndex();
			hasProgressChanged = true;
		}
	}

	if (hasProgressChanged)
	{
		RefreshDebugText();
	}

	if (AreAllSegmentsWalked())
	{
		ForceDrop(m_lastTriggerPlayerIndex);
	}
}

void BurgerIngredientComponent::UpdateDrop()
{
	auto position = GetOwner()->GetPosition();
	const float targetY = m_dropStops[m_nextDropIndex];

	position.y += DROP_SPEED * dae::Timer::GetInstance().GetDeltaTime();

	if (position.y < targetY)
	{
		GetOwner()->SetLocalPosition(position);
		return;
	}

	position.y = targetY;
	GetOwner()->SetLocalPosition(position);

	m_isDropping = false;
	AwardDropScore();
	++m_nextDropIndex;

	if (m_pIngredientBelow != nullptr && !m_pIngredientBelow->IsComplete())
	{
		const float lowerIngredientY = m_pIngredientBelow->GetOwner()->GetPosition().y;
		if (std::abs(lowerIngredientY - position.y) <= CHAIN_TRIGGER_TOLERANCE)
		{
			m_pIngredientBelow->ForceDrop(m_lastTriggerPlayerIndex);
		}
	}

	if (m_nextDropIndex >= m_dropStops.size())
	{
		m_isComplete = true;
		RefreshDebugText();
		return;
	}

	ResetWalkProgress();
	RefreshDebugText();
}

void BurgerIngredientComponent::ResetWalkProgress()
{
	std::fill(m_walkedSegments.begin(), m_walkedSegments.end(), false);
}

void BurgerIngredientComponent::RefreshDebugText() const
{
	auto* pTextComponent = GetOwner()->GetComponent<dae::TextComponent>();
	if (pTextComponent == nullptr)
	{
		return;
	}

	if (m_isComplete)
	{
		pTextComponent->SetText(GetShortLabel() + " DONE");
		pTextComponent->SetColor(SDL_Color{ 160, 160, 160, 255 });
		pTextComponent->Update();
		return;
	}

	const auto walkedCount = static_cast<int>(std::count(m_walkedSegments.begin(), m_walkedSegments.end(), true));
	pTextComponent->SetText(GetShortLabel() + " " + std::to_string(walkedCount) + "/4");
	pTextComponent->Update();
}

void BurgerIngredientComponent::AwardDropScore() const
{
	if (m_lastTriggerPlayerIndex <= 0)
	{
		return;
	}

	auto* pScene = dae::SceneManager::GetInstance().GetCurrentScene();
	if (pScene == nullptr)
	{
		return;
	}

	for (const auto& gameObject : pScene->GetGameObjects())
	{
		auto* pPlayerComponent = gameObject->GetComponent<dae::PlayerComponent>();
		if (pPlayerComponent == nullptr)
		{
			continue;
		}

		if (pPlayerComponent->GetPlayerIndex() == m_lastTriggerPlayerIndex)
		{
			pPlayerComponent->AddScore(BurgerTimeRules::ScorePerStoryPerPart);
			return;
		}
	}
}

bool BurgerIngredientComponent::AreAllSegmentsWalked() const
{
	return std::all_of(m_walkedSegments.begin(), m_walkedSegments.end(),
		[](bool walkedSegment)
		{
			return walkedSegment;
		});
}

std::string BurgerIngredientComponent::GetShortLabel() const
{
	switch (m_type)
	{
	case IngredientType::TopBun:
		return "TOP";
	case IngredientType::BottomBun:
		return "BOT";
	case IngredientType::Patty:
		return "PAT";
	case IngredientType::Cheese:
		return "CHS";
	case IngredientType::Lettuce:
		return "LET";
	case IngredientType::Tomato:
		return "TOM";
	default:
		return "UNK";
	}
}