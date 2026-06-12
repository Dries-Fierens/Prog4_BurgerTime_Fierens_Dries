#pragma once
#include <SDL3/SDL_keycode.h>
#include "SceneManager.h"
#include "GameObject.h"
#include "Font.h"
#include <SDL3/SDL.h>

class Player final
{
public:
	static std::unique_ptr<dae::GameObject> Create(int playerIndex, float x, float y,
		SDL_Keycode left, SDL_Keycode right, SDL_Keycode up, SDL_Keycode down);

	static std::unique_ptr<dae::GameObject> Create(int playerIndex, float x, float y,
		unsigned int controllerIndex);

	static std::vector<std::unique_ptr<dae::GameObject>> CreateUI(const std::shared_ptr<dae::Font>& font,
		int playerIndex, float x, float y);

private:
	static constexpr int ScorePerPickup{ 100 };
	static constexpr float PlayerMoveSpeed{ 200.f };
	static constexpr float PlayerColliderWidth{ 32.f };
	static constexpr float PlayerColliderHeight{ 32.f };
	static constexpr SDL_FRect PeterSourceRect{ 0.f, 0.f, 16.f, 16.f };
};