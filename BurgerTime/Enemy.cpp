#include "Enemy.h"
#include "ColliderComponent.h"
#include "EnemyComponent.h"
#include "EnemySpriteAnimatorComponent.h"
#include "SpriteComponent.h"
#include "SpriteData.h"

std::unique_ptr<dae::GameObject> Enemy::Create(EnemyType type, float x, float y)
{
	auto enemyObject = std::make_unique<dae::GameObject>();
	auto* pEnemy = enemyObject.get();

	enemyObject->SetLocalPosition(x, y);

	auto sprite = std::make_unique<dae::SpriteComponent>("sprites.png", pEnemy);
	sprite->SetSourceRect(BurgerTimeSprites::GetEnemyFrame(type));
	sprite->SetSize(EnemyWidth, EnemyHeight);
	enemyObject->AddComponent(std::move(sprite));

	enemyObject->AddComponent(std::make_unique<EnemySpriteAnimatorComponent>(pEnemy));
	enemyObject->AddComponent(std::make_unique<EnemyComponent>(type, pEnemy));
	enemyObject->AddComponent(std::make_unique<dae::ColliderComponent>(EnemyWidth, EnemyHeight, pEnemy));

	return enemyObject;
}