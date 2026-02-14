#include "Timer.h"

void dae::Timer::Initialize()
{
	m_lastTime = high_resolution_clock::now();
}

void dae::Timer::Update()
{
	steady_clock::time_point m_currentTime = high_resolution_clock::now();
	m_deltaTime = duration<float>(m_currentTime - m_lastTime).count();
	m_lastTime = m_currentTime;
}