#include "BurgerIngredientSpriteComponent.h"
#include "BurgerIngredientComponent.h"
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

	const auto* pIngredientComponent = GetOwner()->GetComponent<BurgerIngredientComponent>();
	if (pIngredientComponent == nullptr)
	{
		return;
	}

	const SDL_FRect fullSource = BurgerTimeSprites::GetIngredientFrame(m_type);
	const glm::vec3 position = GetOwner()->GetPosition();

	const size_t segmentCount = pIngredientComponent->GetSegmentCount();
	if (segmentCount == 0)
	{
		return;
	}

	const float sourceSegmentWidth = fullSource.w / static_cast<float>(segmentCount);
	const float destinationSegmentWidth = m_width / static_cast<float>(segmentCount);

	for (size_t index{}; index < segmentCount; ++index)
	{
		SDL_FRect source{};
		source.x = fullSource.x + sourceSegmentWidth * static_cast<float>(index);
		source.y = fullSource.y;
		source.w = sourceSegmentWidth;
		source.h = fullSource.h;

		SDL_FRect destination{};
		destination.x = position.x + destinationSegmentWidth * static_cast<float>(index);
		destination.y = position.y + (pIngredientComponent->IsSegmentWalked(index) ? m_pressedOffset : 0.f);
		destination.w = destinationSegmentWidth;
		destination.h = m_height;

		dae::Renderer::GetInstance().RenderTexture(*m_texture, destination, source);
	}
}