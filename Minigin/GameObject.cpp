#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"

dae::GameObject::~GameObject() = default;

void dae::GameObject::Update()
{
	UpdateWorldPosition();

	for (const auto& component : m_components)
	{
		component->Update();
	}
}

void dae::GameObject::Render() const
{
	for (const auto& component : m_components)
	{
		component->Render();
	}
}

glm::vec3 dae::GameObject::GetPosition() const
{
	// prevent collider from checking the old pos
	if (m_positionIsDirty)
	{
		const_cast<GameObject*>(this)->UpdateWorldPosition();
	}

	return m_worldPosition;
}

void dae::GameObject::SetLocalPosition(float x, float y)
{
	m_positionIsDirty = true;
	m_transform.SetPosition(x, y, 0.f);
}

void dae::GameObject::SetLocalPosition(glm::vec3 position)
{
	m_positionIsDirty = true;
	m_transform.SetPosition(position);
}