#pragma once
#include "BaseComponent.h"
#include "EventQueue.h"
#include <memory>

namespace dae
{
	class Font;
	class TextComponent;

	class LivesDisplayComponent final : public BaseComponent, public EventListener
	{
	public:
		LivesDisplayComponent(int playerIndex, int initialLives, std::shared_ptr<Font> font, GameObject* pOwner);
		~LivesDisplayComponent() override;

		void Update() override;
		void Render() const override;
		void OnEvent(const Event& event) override;

	private:
		void RefreshText() const;

		int m_playerIndex{};
		int m_lives{};
		std::unique_ptr<TextComponent> m_textComponent;
	};
}