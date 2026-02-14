#pragma once
#include "BaseComponent.h"
#include <string>
#include <memory>
#include <glm/glm.hpp>

namespace dae {

	class Texture2D;
	class RenderComponent final : public BaseComponent
	{
	public:
		RenderComponent(const std::string& filename, GameObject* pOwner);
		RenderComponent(std::shared_ptr<Texture2D> texture, GameObject* pOwner);
		virtual ~RenderComponent() = default;
		RenderComponent(const RenderComponent& other) = delete;
		RenderComponent(RenderComponent&& other) = delete;
		RenderComponent& operator=(const RenderComponent& other) = delete;
		RenderComponent& operator=(RenderComponent&& other) = delete;

		void Update() override;
		void Render() const override;
		void SetTexture(const std::string& filename);
		void SetTexture(std::shared_ptr<Texture2D> texture);

	private:
		std::shared_ptr<Texture2D> m_texture;

	};
}