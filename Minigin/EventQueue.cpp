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
	m_isNotifying = true;

	Event e{};
	while (PollEvent(e))
	{
		for (auto*& listener : m_listeners)
		{
			if (listener)
			{
				listener->OnEvent(e);
			}
		}
	}

	m_isNotifying = false;
	CompactListeners();
}

void dae::EventQueue::AddListener(EventListener* listener)
{
	m_listeners.push_back(listener);
}

void dae::EventQueue::RemoveListener(int listenerId)
{
	for (auto*& listener : m_listeners)
	{
		if (listener && listener->GetId() == listenerId)
		{
			listener = nullptr;
		}
	}

	if (!m_isNotifying)
	{
		CompactListeners();
	}
}

void dae::EventQueue::CompactListeners()
{
	std::erase(m_listeners, nullptr);
}

bool dae::EventQueue::PollEvent(Event& e)
{
	if (m_eventQueue.empty())
		return false;

	e = m_eventQueue.front();
	m_eventQueue.pop();

	return true;
}