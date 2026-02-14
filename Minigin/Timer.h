#pragma once
#include "Singleton.h"
#include <chrono>

using namespace std::chrono;

namespace dae
{
	class Timer final : public Singleton<Timer>
	{
	public:
		void Initialize();
		void Update();
		float GetDeltaTime() const { return m_deltaTime; }
		void SetFixedTimeStep(float fixedTimeStep) { m_fixedTimeStep = fixedTimeStep; }
		float GetFixedTimeStep() const { return m_fixedTimeStep; }

	private:
		steady_clock::time_point m_lastTime{};
		float m_deltaTime{};
		float m_fixedTimeStep{};
	};
}
