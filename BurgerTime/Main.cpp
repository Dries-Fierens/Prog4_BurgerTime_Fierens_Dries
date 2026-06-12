#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#if _DEBUG && __has_include(<vld.h>)
#include <vld.h>
#endif

#include "FPSCounter.h"
#include "InputManager.h"
#include "Minigin.h"
#include "PlayerComponent.h"
#include "RenderComponent.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "SceneManager.h"
#include "TextComponent.h"
#include "Player.h"
#include "Locator.h"
#include "GameManager.h"

#include <filesystem>
namespace fs = std::filesystem;

static void load()
{
	Locator::Initialize();
	GameManager::GetInstance().Initialize();
}

int main(int, char* [])
{
#if __EMSCRIPTEN__
	fs::path data_location = "";
#else
	fs::path data_location = "./Data/";
	if (!fs::exists(data_location))
		data_location = "../Data/";
#endif
	dae::Minigin engine(data_location);
	engine.Run(load);
	return 0;
}