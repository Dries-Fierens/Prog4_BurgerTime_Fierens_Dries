#include "SpriteComponent.h"

#include "GameObject.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "Texture2D.h"

dae::SpriteComponent::SpriteComponent(const std::string& filename, GameObject* pOwner)
	: BaseComponent(pOwner)
{
	SetTexture(filename);
}

dae::SpriteComponent::SpriteComponent(std::shared_ptr<Texture2D> texture, GameObject* pOwner)
	: BaseComponent(pOwner)
	, m_texture(std::move(texture))
{
}

void dae::SpriteComponent::Update()
{
}

void dae::SpriteComponent::Render() const
{
	if (m_texture == nullptr)
	{
		return;
	}

	const auto position = GetOwner()->GetPosition();

	if (!m_hasSourceRect)
	{
		if (m_hasCustomSize)
		{
			Renderer::GetInstance().RenderTexture(*m_texture, position.x, position.y, m_size.x, m_size.y);
		}
		else
		{
			Renderer::GetInstance().RenderTexture(*m_texture, position.x, position.y);
		}

		return;
	}

	SDL_FRect destination{};
	destination.x = position.x;
	destination.y = position.y;
	destination.w = m_hasCustomSize ? m_size.x : m_sourceRect.w;
	destination.h = m_hasCustomSize ? m_size.y : m_sourceRect.h;

	Renderer::GetInstance().RenderTexture(*m_texture, destination, m_sourceRect);
}

void dae::SpriteComponent::SetTexture(const std::string& filename)
{
	m_texture = ResourceManager::GetInstance().LoadTexture(filename);
}

void dae::SpriteComponent::SetTexture(std::shared_ptr<Texture2D> texture)
{
	m_texture = std::move(texture);
}

void dae::SpriteComponent::SetSourceRect(const SDL_FRect& sourceRect)
{
	m_sourceRect = sourceRect;
	m_hasSourceRect = true;
}

void dae::SpriteComponent::SetSize(float width, float height)
{
	m_size = { width, height };
	m_hasCustomSize = true;
}

glm::vec2 dae::SpriteComponent::GetSize() const
{
	if (m_hasCustomSize)
	{
		return m_size;
	}

	if (m_hasSourceRect)
	{
		return { m_sourceRect.w, m_sourceRect.h };
	}

	if (m_texture == nullptr)
	{
		return {};
	}

	return m_texture->GetSize();
}