#pragma once
#include <SDL3/SDL_keycode.h>
#include "SceneManager.h"
#include "GameObject.h"
#include "Font.h"

class Player final
{
public:
	static std::unique_ptr<dae::GameObject> Create(int playerIndex, float x, float y,
		SDL_Keycode left, SDL_Keycode right, SDL_Keycode up, SDL_Keycode down,
		SDL_Keycode dieKey, SDL_Keycode scoreKey);

	static std::unique_ptr<dae::GameObject> Create(int playerIndex, float x, float y,
		unsigned int controllerIndex);

	static std::vector<std::unique_ptr<dae::GameObject>> CreateUI(const std::shared_ptr<dae::Font>& font,
		int playerIndex, float x, float y);
};