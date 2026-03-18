#pragma once
#include "BaseComponent.h"
#include "EventQueue.h"
#include <memory>

namespace dae
{
	class Font;
	class TextComponent;

	class ScoreDisplayComponent final : public BaseComponent, public EventListener
	{
	public:
		ScoreDisplayComponent(int playerIndex, int initialScore, std::shared_ptr<Font> font, GameObject* pOwner);
		~ScoreDisplayComponent() override;

		void Update() override;
		void Render() const override;
		void OnEvent(const Event& event) override;

	private:
		void RefreshText() const;

		int m_playerIndex{};
		int m_score{};
		std::unique_ptr<TextComponent> m_textComponent;
	};
}