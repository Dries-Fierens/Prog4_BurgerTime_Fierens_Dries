#include "LivesDisplayComponent.h"
#include "TextComponent.h"
#include <string>

dae::LivesDisplayComponent::LivesDisplayComponent(int playerIndex, int initialLives, std::shared_ptr<Font> font, GameObject* pOwner)
	: BaseComponent(pOwner)
	, EventListener()
	, m_playerIndex(playerIndex)
	, m_lives(initialLives)
	, m_textComponent(std::make_unique<TextComponent>("", font, pOwner))
{
	EventQueue::GetInstance().AddListener(this);
	RefreshText();
}

dae::LivesDisplayComponent::~LivesDisplayComponent()
{
	EventQueue::GetInstance().RemoveListener(GetId());
}

void dae::LivesDisplayComponent::Update()
{
	m_textComponent->Update();
}

void dae::LivesDisplayComponent::Render() const
{
	m_textComponent->Render();
}

void dae::LivesDisplayComponent::OnEvent(const Event& event)
{
	if (event.name != "PlayerDied" || event.playerIndex != m_playerIndex)
	{
		return;
	}

	m_lives = event.value;
	RefreshText();
}

void dae::LivesDisplayComponent::RefreshText() const
{
	m_textComponent->SetText("P" + std::to_string(m_playerIndex) + " Lives: " + std::to_string(m_lives));
	m_textComponent->Update();
}