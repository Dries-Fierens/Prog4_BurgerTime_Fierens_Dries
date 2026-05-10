#include "ScoreDisplayComponent.h"
#include "TextComponent.h"
#include <string>

dae::ScoreDisplayComponent::ScoreDisplayComponent(int playerIndex, int initialScore, std::shared_ptr<Font> font, GameObject* pOwner)
	: BaseComponent(pOwner)
	, EventListener()
	, m_playerIndex(playerIndex)
	, m_score(initialScore)
	, m_textComponent(std::make_unique<TextComponent>("", font, pOwner))
{
	EventQueue::GetInstance().AddListener(this);
	RefreshText();
}

dae::ScoreDisplayComponent::~ScoreDisplayComponent()
{
	EventQueue::GetInstance().RemoveListener(GetId());
}

void dae::ScoreDisplayComponent::Update()
{
	m_textComponent->Update();
}

void dae::ScoreDisplayComponent::Render() const
{
	m_textComponent->Render();
}

void dae::ScoreDisplayComponent::OnEvent(const Event& event)
{
	if (event.name != "ScoreChanged" || event.playerIndex != m_playerIndex)
	{
		return;
	}

	m_score = event.value;
	RefreshText();
}

void dae::ScoreDisplayComponent::RefreshText() const
{
	m_textComponent->SetText("P" + std::to_string(m_playerIndex) + " Score: " + std::to_string(m_score));
	m_textComponent->Update();
}