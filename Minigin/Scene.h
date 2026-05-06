#pragma once
#include <memory>
#include <string>
#include <vector>
#include "GameObject.h"

namespace dae
{
	class Scene final
	{
	public:
		void Add(std::unique_ptr<GameObject> object);
		void Remove(const GameObject& object);
		void RemoveAll();

		void Update();
		void Render() const;

		std::vector<std::unique_ptr<GameObject>>& GetGameObjects();
		const std::vector<std::unique_ptr<GameObject>>& GetGameObjects() const;

		const std::string& GetName() const;
		void SetName(const std::string& name);

		~Scene() = default;
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	private:
		friend class SceneManager;
		explicit Scene(const std::string& name);

		std::string m_name{};
		std::vector<std::unique_ptr<GameObject>> m_objects{};
	};
}