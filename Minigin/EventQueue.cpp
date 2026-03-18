#include "EventQueue.h"

int EventListener::m_idCounter{ 0 };

EventListener::EventListener()
{
	m_id = m_idCounter;
	++m_idCounter;
}

void dae::EventQueue::SendEvent(const Event& event)
{
	m_eventQueue.push(event);
}

void dae::EventQueue::NotifyListeners()
{
	Event e{};
	while (PollEvent(e))
	{
		for (auto listener : m_listeners)
		{
			listener->OnEvent(e);
		}
	}
}

void dae::EventQueue::AddListener(EventListener* listener)
{
	m_listeners.push_back(listener);
}

void dae::EventQueue::RemoveListener(int listenerId)
{
	std::vector<EventListener*> newListeners;

	for (auto* listener : m_listeners)
	{
		if (listener && listener->GetId() != listenerId)
		{
			newListeners.push_back(listener);
		}
	}

	m_listeners = newListeners;
}

bool dae::EventQueue::PollEvent(Event& e)
{
	if (m_eventQueue.empty())
		return false;

	e = m_eventQueue.front();
	m_eventQueue.pop();

	return true;
}
