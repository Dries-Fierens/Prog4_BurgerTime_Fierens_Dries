#include "BurgerIngredientSpriteComponent.h"
#include "GameObject.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "SpriteData.h"
#include "Texture2D.h"

#include <SDL3/SDL.h>

BurgerIngredientSpriteComponent::BurgerIngredientSpriteComponent(IngredientType type, float width, float height, dae::GameObject* pOwner)
	: BaseComponent(pOwner)
	, m_type(type)
	, m_width(width)
	, m_height(height)
{
	m_texture = dae::ResourceManager::GetInstance().LoadTexture("sprites.png");
}

void BurgerIngredientSpriteComponent::Update()
{
}

void BurgerIngredientSpriteComponent::Render() const
{
	if (m_texture == nullptr)
	{
		return;
	}

	const SDL_FRect source = BurgerTimeSprites::GetIngredientFrame(m_type);
	const glm::vec3 position = GetOwner()->GetPosition();

	const float segmentWidth = m_width / 4.f;

	for (int index{}; index < 4; ++index)
	{
		SDL_FRect destination{};
		destination.x = position.x + segmentWidth * static_cast<float>(index);
		destination.y = position.y;
		destination.w = segmentWidth;
		destination.h = m_height;

		dae::Renderer::GetInstance().RenderTexture(*m_texture, destination, source);
	}
}