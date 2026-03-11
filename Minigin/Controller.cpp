#include "Controller.h"
#include <windows.h>
#include <XInput.h>

class dae::Controller::ControllerImpl final
{
public:
	ControllerImpl(int controllerIndex)
		: m_buttonsPressed{}, m_buttonsReleased{}, m_controllerIndex{ controllerIndex }
	{
		ZeroMemory(&m_prevState, sizeof(XINPUT_STATE));
		ZeroMemory(&m_currState, sizeof(XINPUT_STATE));
	}

	void Update()
	{
		CopyMemory(&m_prevState, &m_currState, sizeof(XINPUT_STATE));
		ZeroMemory(&m_currState, sizeof(XINPUT_STATE));
		XInputGetState(m_controllerIndex, &m_currState);

		auto buttonChanges = m_currState.Gamepad.wButtons ^ m_prevState.Gamepad.wButtons;
		m_buttonsPressed = buttonChanges & m_currState.Gamepad.wButtons;
		m_buttonsReleased = buttonChanges & (~m_currState.Gamepad.wButtons);
	}

	bool IsDown(unsigned int button) const { return m_buttonsPressed & button; }
	bool IsUp(unsigned int button) const { return m_buttonsReleased & button; }
	bool IsPressed(unsigned int button) const { return m_currState.Gamepad.wButtons & button; }
	glm::vec2 GetLeftStickPos() const { return glm::vec2{ m_currState.Gamepad.sThumbLX, m_currState.Gamepad.sThumbLY }; }

private:
	XINPUT_STATE m_prevState{};
	XINPUT_STATE m_currState{};
	WORD m_buttonsPressed;
	WORD m_buttonsReleased;
	int m_controllerIndex;
};

dae::Controller::Controller(unsigned int controllerIndex)
	: m_controllerIndex{ controllerIndex }
{
	m_pImpl = std::make_unique<ControllerImpl>(controllerIndex);
}

dae::Controller::~Controller()
{
}

void dae::Controller::Update()
{
	m_pImpl->Update();
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
