#pragma once
#include "BaseComponent.h"
#include "LevelData.h"

#include <memory>

namespace dae
{
	class Texture2D;
}

class BurgerIngredientSpriteComponent final : public dae::BaseComponent
{
public:
	BurgerIngredientSpriteComponent(IngredientType type, float width, float height, dae::GameObject* pOwner);

	void Update() override;
	void Render() const override;

private:
	IngredientType m_type{};
	float m_width{};
	float m_height{};
	std::shared_ptr<dae::Texture2D> m_texture{};

	const float m_pressedOffset{ 8.f };
};