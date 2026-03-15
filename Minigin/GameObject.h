#pragma once
#include <memory>
#include <vector>
#include <typeindex>
#include <type_traits>
#include <algorithm>
#include <string>
#include "Transform.h"
#include "BaseComponent.h"

namespace dae
{
	class Texture2D;
	class GameObject final
	{
	public:
		void Update();
		void Render() const;

        glm::vec3 GetPosition() const;
		void SetLocalPosition(float x, float y);
        void SetLocalPosition(glm::vec3 position);

		GameObject() = default;
		~GameObject();
        GameObject(GameObject* parent) { SetParent(parent); };
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

        template <typename ComponentType, typename... Args>
        std::shared_ptr<ComponentType> AddComponent(std::shared_ptr<ComponentType> component)
        {
            static_assert(std::is_base_of<BaseComponent, ComponentType>::value, "ComponentType must derive from BaseComponent");

            m_components.emplace_back(component);

            return component;
        }

        template <typename ComponentType>
        void RemoveComponent(std::shared_ptr<ComponentType> component)
        {
            static_assert(std::is_base_of<BaseComponent, ComponentType>::value, "ComponentType must derive from BaseComponent");

            m_components.erase(
                std::remove_if(m_components.begin(), m_components.end(),
                    [&component](const std::shared_ptr<BaseComponent>& currentComponent)
                    {
                        return currentComponent == component;
                    }),
                m_components.end());
        }

        template <typename ComponentType>
        std::shared_ptr<ComponentType> GetComponent() const
        {
            static_assert(std::is_base_of<BaseComponent, ComponentType>::value, "ComponentType must derive from BaseComponent");

            for (const auto& component : m_components)
            {
                if (auto castedComponent = std::dynamic_pointer_cast<ComponentType>(component))
                {
                    return castedComponent;
                }
            }
            return nullptr;
        }

        template <typename ComponentType>
        bool HasComponent() const
        {
            static_assert(std::is_base_of<BaseComponent, ComponentType>::value, "ComponentType must derive from BaseComponent");

            return std::any_of(m_components.begin(), m_components.end(),
                [](const std::shared_ptr<BaseComponent>& component)
                {
                    return std::dynamic_pointer_cast<ComponentType>(component) != nullptr;
                });
        }

        GameObject* GetParent() const
        {
            return m_parent;
        }

        void SetParent(GameObject* parent, bool keepWorldPosition = true)
        {
            if (parent == this || IsChild(parent) || m_parent == parent) return;

            const glm::vec3 worldPosition{ GetWorldPosition() };

            if (m_parent) m_parent->RemoveChild(this);

            m_parent = parent;

            if (m_parent) m_parent->AddChild(this);

            if (keepWorldPosition)
            {
                if (m_parent == nullptr)
                    SetLocalPosition(worldPosition);
                else
                    SetLocalPosition(worldPosition - m_parent->GetWorldPosition());
            }
            else
            {
                m_positionIsDirty = true;
            }
        }

        //void SetParent(GameObject* parent)
        //{
        //    if (parent == this || IsChild(parent)) return;

        //    if (parent == nullptr)
        //        SetLocalPosition(GetWorldPosition());
        //    else
        //        m_positionIsDirty = true;

        //    if (m_parent) m_parent->RemoveChild(this);

        //    m_parent = parent;

        //    if (m_parent) m_parent->AddChild(this);
        //}

        size_t GetChildCount() const
        {
            return m_children.size();
        }

        GameObject* GetChildAt(unsigned int index) const
        {
            if (index < 0 || index >= m_children.size())
            {
                return nullptr;
            }
            return m_children[index];
        }

    private:
        void AddChild(GameObject* child)
        {
            if (child == nullptr || IsParent(child))
            {
                return;
            }

            if (child->m_parent)
            {
                child->m_parent->RemoveChild(child);
            }

            child->m_parent = this;
            m_children.emplace_back(child);

            UpdateWorldPosition();
        }

        void RemoveChild(GameObject* child)
        {
            if (child == nullptr || !IsChild(child))
            {
                return;
            }

            m_children.erase(std::remove(m_children.begin(), m_children.end(), child), m_children.end());

            child->m_parent = nullptr;

            UpdateWorldPosition();
        }

        bool IsChild(GameObject* otherChild) const
        {
            for (const auto& child : m_children)
            {
                if (child == otherChild || child->IsChild(otherChild))
                {
                    return true;
                }
            }
            return false;
        }

        bool IsParent(GameObject* otherParent) const
        {
            if (m_parent == nullptr)
            {
                return false;
            }

            if (m_parent == otherParent)
            {
                return true;
            }

            return m_parent->IsParent(otherParent);
        }

        const glm::vec3& GetWorldPosition()
        {
            if (m_positionIsDirty)
                UpdateWorldPosition();
            return m_worldPosition;
        }

        void UpdateWorldPosition()
        {
            if (m_positionIsDirty)
            {
                if (m_parent == nullptr)
                    m_worldPosition = m_transform.GetPosition();
                else
                    m_worldPosition = m_parent->GetWorldPosition() + m_transform.GetPosition();
            }
            m_positionIsDirty = false;
        }

        Transform m_transform{};
        std::vector<std::shared_ptr<BaseComponent>> m_components;
        GameObject* m_parent{ nullptr };
        std::vector<GameObject*> m_children;
        glm::vec3 m_worldPosition{};
        bool m_positionIsDirty{ true };
	};
}
