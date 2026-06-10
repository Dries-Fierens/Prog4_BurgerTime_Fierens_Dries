#include "BurgerProgressComponent.h"
#include "BurgerIngredientComponent.h"
#include "EventQueue.h"
#include <algorithm>

BurgerProgressComponent::BurgerProgressComponent(dae::GameObject* pOwner)
	: BaseComponent(pOwner)
{
}

void BurgerProgressComponent::Update()
{
	if (m_hasTriggeredNextLevel || m_pIngredients.empty())
	{
		return;
	}

	const bool areAllIngredientsComplete = std::all_of(m_pIngredients.begin(), m_pIngredients.end(),
		[](const BurgerIngredientComponent* pIngredient)
		{
			return pIngredient != nullptr && pIngredient->IsComplete();
		});

	if (!areAllIngredientsComplete)
	{
		return;
	}

	Event event{};
	event.name = "NextLevel";
	dae::EventQueue::GetInstance().SendEvent(event);
	m_hasTriggeredNextLevel = true;
}

void BurgerProgressComponent::Render() const
{
}

void BurgerProgressComponent::SetIngredients(const std::vector<BurgerIngredientComponent*>& ingredients)
{
	m_pIngredients = ingredients;
}