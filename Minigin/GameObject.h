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
		virtual void Update();
		virtual void Render() const;

        glm::vec2 GetPosition() const;
		void SetPosition(float x, float y);

		GameObject() = default;
		virtual ~GameObject();
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

            auto it = std::remove_if(m_components.begin(), m_components.end(), [](const std::shared_ptr<BaseComponent>& component)
                {
                    return typeid(*component) == typeid(ComponentType);
                });

            if (it != m_components.end())
            {
                m_components.erase(it, m_components.end());
            }
        }

        template <typename ComponentType>
        std::shared_ptr<ComponentType> GetComponent() const
        {
            static_assert(std::is_base_of<BaseComponent, ComponentType>::value, "ComponentType must derive from BaseComponent");

            for (const auto& component : m_components)
            {
                if (typeid(*component) == typeid(ComponentType))
                {
                    return std::static_pointer_cast<ComponentType>(component);
                }
            }
            return nullptr;
        }

        template <typename ComponentType>
        bool HasComponent() const
        {
            static_assert(std::is_base_of<BaseComponent, ComponentType>::value, "ComponentType must derive from BaseComponent");

            return std::any_of(m_components.begin(), m_components.end(), [](const std::shared_ptr<BaseComponent>& component)
                {
                    return typeid(*component) == typeid(ComponentType);
                });
        }

    private:
        Transform m_transform{};
        std::vector<std::shared_ptr<BaseComponent>> m_components;

	};
}
