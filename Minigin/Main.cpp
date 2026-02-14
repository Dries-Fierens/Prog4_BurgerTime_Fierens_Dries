#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#if _DEBUG && __has_include(<vld.h>)
#include <vld.h>
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "TextComponent.h"
#include "FPSCounter.h"
#include "Scene.h"

#include <filesystem>
namespace fs = std::filesystem;

static void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene();

	auto go = std::make_unique<dae::GameObject>();
	auto background = std::make_shared<dae::RenderComponent>("background.png", go.get());
	go->AddComponent(background);
	scene.Add(std::move(go));

	go = std::make_unique<dae::GameObject>();
	auto logoDAE = std::make_shared<dae::RenderComponent>("logo.png", go.get());
	go->AddComponent(logoDAE);
	go->SetPosition(358, 180);
	scene.Add(std::move(go));

	go = std::make_unique<dae::GameObject>();
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto text = std::make_shared<dae::TextComponent>("Programming 4 Assignment", font, go.get());
	text->SetColor({ 255, 255, 0, 255 });
	go->AddComponent(text);
	go->SetPosition(292, 20);
	scene.Add(std::move(go));

	go = std::make_unique<dae::GameObject>();
	auto fpsComponent = std::make_shared<dae::FPSCounter>(font, go.get());
	go->AddComponent(fpsComponent);
	go->SetPosition(10, 10);
	scene.Add(std::move(go));
}

int main(int, char*[]) {
#if __EMSCRIPTEN__
	fs::path data_location = "";
#else
	fs::path data_location = "./Data/";
	if(!fs::exists(data_location))
		data_location = "../Data/";
#endif
	dae::Minigin engine(data_location);
	engine.Run(load);
    return 0;
}
