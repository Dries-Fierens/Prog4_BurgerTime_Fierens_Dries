#pragma once
#include "Singleton.h"
#include "Command.h"
#include "Controller.h"
#include <map>
#include <memory>
#include <string>
#include <vector>
#include <SDL3/SDL.h>
#include <backends/imgui_impl_sdl3.h>
#include <iostream>
#include <sstream>
#include <algorithm>

namespace dae
{
	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();

		enum class InputType
		{
			OnDown,
			OnPressed,
			OnRelease
		};

		void AddControllerCommand(std::unique_ptr<Command> pCommand, Controller::ButtonState button, unsigned int controllerIndex, InputType type);
		void AddKeyboardCommand(std::unique_ptr<Command> pCommand, SDL_Keycode keyboardKey, InputType type);
		void RemoveInputs();

	private:
		struct ControllerInput
		{
			unsigned int controllerIndex{};
			Controller::ButtonState button{};
			InputType type{};

			bool operator<(const ControllerInput& other) const
			{
				if (controllerIndex < other.controllerIndex) return true;
				if (controllerIndex > other.controllerIndex) return false;

				if (button < other.button) return true;
				if (button > other.button) return false;

				return type < other.type;
			}
		};

		struct KeyboardInput
		{
			SDL_Keycode key{};
			InputType type{};

			bool operator<(const KeyboardInput& other) const
			{
				if (key < other.key) return true;
				if (key > other.key) return false;

				return type < other.type;
			}
		};

		std::map<ControllerInput, std::unique_ptr<Command>> m_pControllerMap{};
		std::vector<std::unique_ptr<Controller>> m_pControllers{};
		std::map<KeyboardInput, std::unique_ptr<Command>> m_pKeyboardMap{};
		std::vector<SDL_Keycode> m_PressedKeys{};
	};
}