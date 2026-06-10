#pragma once
#include "GameObject.h"
#include "LevelData.h"
#include <memory>

class Enemy final
{
public:
	static std::unique_ptr<dae::GameObject> Create(EnemyType type, float x, float y);

private:
	static constexpr float EnemyWidth{ 32.f };
	static constexpr float EnemyHeight{ 32.f };
};