#include "InputManager.h"

bool dae::InputManager::ProcessInput()
{
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_EVENT_QUIT)
		{
			return false;
		}

		// Handle window events
		size_t prevSize = dae::InputManager::m_pKeyboardMap.size();
		for (auto& map : m_pKeyboardMap)
		{
			if (e.key.key == map.first.key)
			{
				if (map.first.type == InputType::OnDown && e.type == SDL_EVENT_KEY_DOWN)
				{
					if (std::ranges::find(m_PressedKeys, map.first.key) != m_PressedKeys.end())
						continue;

					map.second->Execute();
				}
				else if (map.first.type == InputType::OnRelease && e.type == SDL_EVENT_KEY_DOWN)
				{
					map.second->Execute();
				}

				if (m_pKeyboardMap.size() != prevSize)
				{
					break;
				}
			}
		}

		//process event for IMGUI
		ImGui_ImplSDL3_ProcessEvent(&e);
	}

	// Clear previously pressed keys
	m_PressedKeys.clear();

	// Process keyboard inputs
	const auto* state = SDL_GetKeyboardState(nullptr);
	for (auto& map : m_pKeyboardMap)
	{
		const SDL_Scancode scancode = SDL_GetScancodeFromKey(map.first.key, nullptr);
		if (scancode != SDL_SCANCODE_UNKNOWN && state[scancode])
		{
			m_PressedKeys.push_back(map.first.key);

			if (map.first.type == InputType::OnPressed)
			{
				map.second->Execute();
			}
		}
	}

	// Process controller inputs
	for (auto& controller : m_pControllers)
	{
		controller->Update();

		for (auto& map : m_pControllerMap)
		{
			if (map.first.controllerIndex == controller->GetIndex())
			{
				if ((map.first.type == InputType::OnDown && controller->IsDown(map.first.button)) ||
					(map.first.type == InputType::OnPressed && controller->IsPressed(map.first.button)) ||
					(map.first.type == InputType::OnRelease && controller->IsUp(map.first.button)))
				{
					map.second->Execute();
				}
			}
		}
	}

	return true;
}

void dae::InputManager::AddControllerCommand(std::unique_ptr<Command> pCommand, Controller::ButtonState button, unsigned int controllerIndex, InputType type)
{
	bool controllerExists = false;
	for (const auto& controller : m_pControllers)
	{
		if (controller->GetIndex() == controllerIndex)
		{
			controllerExists = true;
			break;
		}
	}

	if (controllerExists == false)
	{
		m_pControllers.push_back(std::make_unique<Controller>(controllerIndex));
	}

	ControllerInput input{ controllerIndex, button, type };
	m_pControllerMap.insert(std::pair(input, std::move(pCommand)));
}

void dae::InputManager::AddKeyboardCommand(std::unique_ptr<Command> pCommand, SDL_Keycode keyboardKey, InputType type)
{
	KeyboardInput input{ keyboardKey, type };
	m_pKeyboardMap.insert(std::pair(input, std::move(pCommand)));
}

void dae::InputManager::RemoveInputs()
{
	m_pControllerMap.clear();
	m_pKeyboardMap.clear();
}