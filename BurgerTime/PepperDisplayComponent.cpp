#include "PepperDisplayComponent.h"
#include "TextComponent.h"

#include <string>

dae::PepperDisplayComponent::PepperDisplayComponent(int playerIndex, int initialPepperShots, std::shared_ptr<Font> font, GameObject* pOwner)
	: BaseComponent(pOwner)
	, EventListener()
	, m_playerIndex(playerIndex)
	, m_pepperShots(initialPepperShots)
	, m_textComponent(std::make_unique<TextComponent>("", font, pOwner))
{
	EventQueue::GetInstance().AddListener(this);
	RefreshText();
}

dae::PepperDisplayComponent::~PepperDisplayComponent()
{
	EventQueue::GetInstance().RemoveListener(GetId());
}

void dae::PepperDisplayComponent::Update()
{
	m_textComponent->Update();
}

void dae::PepperDisplayComponent::Render() const
{
	m_textComponent->Render();
}

void dae::PepperDisplayComponent::OnEvent(const Event& event)
{
	if (event.name != "PepperChanged" || event.playerIndex != m_playerIndex)
	{
		return;
	}

	m_pepperShots = event.value;
	RefreshText();
}

void dae::PepperDisplayComponent::RefreshText() const
{
	m_textComponent->SetText("P" + std::to_string(m_playerIndex) + " Pepper: " + std::to_string(m_pepperShots));
	m_textComponent->SetColor({ 255, 255, 255, 255 });
	m_textComponent->Update();
}