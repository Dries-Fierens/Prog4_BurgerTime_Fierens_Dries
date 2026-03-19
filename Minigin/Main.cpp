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

#include <filesystem>
namespace fs = std::filesystem;

static void load()
{
	dae::InputManager::GetInstance().RemoveInputs();

	auto& scene = dae::SceneManager::GetInstance().CreateScene();

	auto go = std::make_unique<dae::GameObject>();
	auto background = std::make_unique<dae::RenderComponent>("background.png", go.get());
	go->AddComponent(std::move(background));
	scene.Add(std::move(go));

	go = std::make_unique<dae::GameObject>();
	auto logoDAE = std::make_unique<dae::RenderComponent>("logo.png", go.get());
	go->AddComponent(std::move(logoDAE));
	go->SetLocalPosition(358, 180);
	scene.Add(std::move(go));

	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

	go = std::make_unique<dae::GameObject>();
	auto text = std::make_unique<dae::TextComponent>("Programming 4 Assignment", font, go.get());
	text->SetColor({ 255, 255, 0, 255 });
	go->AddComponent(std::move(text));
	go->SetLocalPosition(292, 20);
	scene.Add(std::move(go));

	go = std::make_unique<dae::GameObject>();
	auto fpsComponent = std::make_unique<dae::FPSCounter>(font, go.get());
	go->AddComponent(std::move(fpsComponent));
	go->SetLocalPosition(10, 10);
	scene.Add(std::move(go));

	// Temporary to create UI for the players
	Player::CreateUI(scene, font, 1, 10.f, 60.f);
	Player::CreateUI(scene, font, 2, 720.f, 60.f);

	Player::Create(scene, 1, 280.f, 280.f, 'a', 'd', 'w', 's', 'q', 'e');
	Player::Create(scene, 2, 640.f, 280.f, 'j', 'l', 'i', 'k', 'u', 'o');
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