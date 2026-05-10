#include "EventQueue.h"
#include <algorithm>

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
		const auto listenersSnapshot = m_listeners;

		for (auto* listener : listenersSnapshot)
		{
			if (listener == nullptr)
			{
				continue;
			}

			const auto it = std::find(m_listeners.begin(), m_listeners.end(), listener);
			if (it == m_listeners.end())
			{
				continue;
			}

			listener->OnEvent(e);
		}
	}
}

void dae::EventQueue::AddListener(EventListener* listener)
{
	if (listener == nullptr)
	{
		return;
	}

	const auto it = std::find(m_listeners.begin(), m_listeners.end(), listener);
	if (it == m_listeners.end())
	{
		m_listeners.push_back(listener);
	}
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