#include "SceneManager.h"
#include "Scene.h"

void dae::SceneManager::Update()
{
	for(auto& scene : m_scenes)
	{
		scene->Update();
	}
}

void dae::SceneManager::Render()
{
	for (const auto& scene : m_scenes)
	{
		scene->Render();
	}
}

dae::Scene& dae::SceneManager::CreateScene(const std::string& name)
{
	m_scenes.emplace_back(new Scene(name));
	return *m_scenes.back();
}

void dae::SceneManager::SetCurrentScene(const Scene* pScene)
{
	for (size_t i = 0; i < m_scenes.size(); ++i)
	{
		if (m_scenes[i].get() == pScene) m_currentScene = static_cast<int>(i);
	}
}

void dae::SceneManager::SetCurrentScene(const std::string& name)
{
	for (size_t i = 0; i < m_scenes.size(); ++i)
	{
		if (m_scenes[i]->GetName() == name) m_currentScene = static_cast<int>(i);
	}
}

dae::Scene* dae::SceneManager::GetCurrentScene() const
{
	if (m_currentScene != -1 && m_scenes.size() != 0) return m_scenes[m_currentScene].get();
	return nullptr;
}
