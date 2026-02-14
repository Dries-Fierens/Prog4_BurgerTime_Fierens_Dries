#include "RenderComponent.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "Renderer.h"
#include "Texture2D.h"

dae::RenderComponent::RenderComponent(const std::string& filename, GameObject* pOwner) : BaseComponent(pOwner)
{
	SetTexture(filename);
}

dae::RenderComponent::RenderComponent(std::shared_ptr<Texture2D> texture, GameObject* pOwner) : BaseComponent(pOwner)
{
	SetTexture(texture);
}

void dae::RenderComponent::Update()
{
}

void dae::RenderComponent::Render() const
{
	if (m_texture)
	{
		const auto pos = GetOwner()->GetPosition();
		Renderer::GetInstance().RenderTexture(*m_texture, pos.x, pos.y);
	}
}

void dae::RenderComponent::SetTexture(const std::string& filename)
{
	m_texture = ResourceManager::GetInstance().LoadTexture(filename);
}

void dae::RenderComponent::SetTexture(std::shared_ptr<Texture2D> texture)
{
	m_texture = texture;
}
