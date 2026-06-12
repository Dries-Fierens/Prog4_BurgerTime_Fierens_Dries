#pragma once
#include "BaseComponent.h"
#include "EventQueue.h"

#include <memory>

namespace dae
{
	class Font;
	class TextComponent;

	class PepperDisplayComponent final : public BaseComponent, public EventListener
	{
	public:
		PepperDisplayComponent(int playerIndex, int initialPepperShots, std::shared_ptr<Font> font, GameObject* pOwner);
		~PepperDisplayComponent() override;

		void Update() override;
		void Render() const override;
		void OnEvent(const Event& event) override;

	private:
		void RefreshText() const;

		int m_playerIndex{};
		int m_pepperShots{};
		std::unique_ptr<TextComponent> m_textComponent;
	};
}