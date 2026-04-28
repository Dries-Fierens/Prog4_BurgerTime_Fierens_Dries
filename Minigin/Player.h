#pragma once
#include <SDL3/SDL_keycode.h>
#include "SceneManager.h"
#include "GameObject.h"
#include "Font.h"

class Player final
{
public:
	static void Create(dae::Scene& scene, int playerIndex, float x, float y,
		SDL_Keycode left, SDL_Keycode right, SDL_Keycode up, SDL_Keycode down,
		SDL_Keycode dieKey, SDL_Keycode scoreKey);

	static void Create(dae::Scene& scene, int playerIndex, float x, float y,
		unsigned int controllerIndex);

	static void CreateUI(dae::Scene& scene, const std::shared_ptr<dae::Font>& font,
		int playerIndex, float x, float y);
};