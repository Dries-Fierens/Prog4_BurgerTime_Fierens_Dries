#include "Controller.h"

#if defined(_WIN32) && !defined(__EMSCRIPTEN__)
#include <windows.h>
#include <XInput.h>
#pragma comment(lib, "xinput.lib")

class dae::Controller::ControllerImpl final
{
public:
	explicit ControllerImpl(unsigned int controllerIndex)
		: m_buttonsPressed{}
		, m_buttonsReleased{}
		, m_controllerIndex{ controllerIndex }
	{
		ZeroMemory(&m_prevState, sizeof(XINPUT_STATE));
		ZeroMemory(&m_currState, sizeof(XINPUT_STATE));
	}

	void Update()
	{
		CopyMemory(&m_prevState, &m_currState, sizeof(XINPUT_STATE));
		ZeroMemory(&m_currState, sizeof(XINPUT_STATE));
		XInputGetState(m_controllerIndex, &m_currState);

		const auto buttonChanges = m_currState.Gamepad.wButtons ^ m_prevState.Gamepad.wButtons;
		m_buttonsPressed = buttonChanges & m_currState.Gamepad.wButtons;
		m_buttonsReleased = buttonChanges & (~m_currState.Gamepad.wButtons);
	}

	bool IsDown(unsigned int button) const
	{
		return (m_buttonsPressed & button) != 0;
	}

	bool IsUp(unsigned int button) const
	{
		return (m_buttonsReleased & button) != 0;
	}

	bool IsPressed(unsigned int button) const
	{
		return (m_currState.Gamepad.wButtons & button) != 0;
	}

	glm::vec2 GetLeftStickPos() const
	{
		return glm::vec2{ m_currState.Gamepad.sThumbLX, m_currState.Gamepad.sThumbLY };
	}

	unsigned int GetIndex() const
	{
		return m_controllerIndex;
	}

private:
	XINPUT_STATE m_prevState{};
	XINPUT_STATE m_currState{};
	WORD m_buttonsPressed{};
	WORD m_buttonsReleased{};
	unsigned int m_controllerIndex{};
};

#else

class dae::Controller::ControllerImpl final
{
public:
	explicit ControllerImpl(unsigned int controllerIndex)
		: m_controllerIndex{ controllerIndex }
	{
	}

	void Update()
	{
	}

	bool IsDown(unsigned int) const
	{
		return false;
	}

	bool IsUp(unsigned int) const
	{
		return false;
	}

	bool IsPressed(unsigned int) const
	{
		return false;
	}

	glm::vec2 GetLeftStickPos() const
	{
		return glm::vec2{ 0.f, 0.f };
	}

	unsigned int GetIndex() const
	{
		return m_controllerIndex;
	}

private:
	unsigned int m_controllerIndex{};
};

#endif

dae::Controller::Controller(unsigned int controllerIndex)
	: m_pImpl{ std::make_unique<ControllerImpl>(controllerIndex) }
{
}

dae::Controller::~Controller() = default;

void dae::Controller::Update()
{
	m_pImpl->Update();
}

unsigned int dae::Controller::GetIndex() const
{
	return m_pImpl->GetIndex();
}

bool dae::Controller::IsDown(ButtonState button) const
{
	return m_pImpl->IsDown(static_cast<unsigned int>(button));
}

bool dae::Controller::IsUp(ButtonState button) const
{
	return m_pImpl->IsUp(static_cast<unsigned int>(button));
}

bool dae::Controller::IsPressed(ButtonState button) const
{
	return m_pImpl->IsPressed(static_cast<unsigned int>(button));
}

glm::vec2 dae::Controller::GetLeftStickPos() const
{
	return m_pImpl->GetLeftStickPos();
}