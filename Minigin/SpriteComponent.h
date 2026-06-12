#pragma once
#include "BaseComponent.h"
#include <SDL3/SDL.h>
#include <glm/vec2.hpp>
#include <memory>
#include <string>

namespace dae
{
	class Texture2D;

	class SpriteComponent final : public BaseComponent
	{
	public:
		SpriteComponent(const std::string& filename, GameObject* pOwner);
		SpriteComponent(std::shared_ptr<Texture2D> texture, GameObject* pOwner);

		void Update() override;
		void Render() const override;

		void SetTexture(const std::string& filename);
		void SetTexture(std::shared_ptr<Texture2D> texture);
		void SetSourceRect(const SDL_FRect& sourceRect);
		void SetSize(float width, float height);
		void SetFlipHorizontal(bool flipHorizontal);

		glm::vec2 GetSize() const;

	private:
		std::shared_ptr<Texture2D> m_texture{};
		SDL_FRect m_sourceRect{};
		bool m_hasSourceRect{};
		glm::vec2 m_size{};
		bool m_hasCustomSize{};
		bool m_flipHorizontal{};
	};
}