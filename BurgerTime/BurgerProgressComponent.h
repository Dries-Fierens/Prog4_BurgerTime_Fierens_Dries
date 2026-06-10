#pragma once
#include "BaseComponent.h"
#include <vector>

class BurgerIngredientComponent;

class BurgerProgressComponent final : public dae::BaseComponent
{
public:
	explicit BurgerProgressComponent(dae::GameObject* pOwner);

	void Update() override;
	void Render() const override;

	void SetIngredients(const std::vector<BurgerIngredientComponent*>& ingredients);

private:
	std::vector<BurgerIngredientComponent*> m_pIngredients{};
	bool m_hasTriggeredNextLevel{};
};