#pragma once
#include "BaseComponent.h"
#include "LevelData.h"
#include <vector>
#include <string>

class BurgerIngredientComponent final : public dae::BaseComponent
{
public:
	BurgerIngredientComponent(IngredientType type, float width, std::vector<float> dropStops, dae::GameObject* pOwner);

	void Update() override;
	void Render() const override;

	void SetIngredientBelow(BurgerIngredientComponent* pIngredientBelow);
	void ForceDrop(int playerIndex);

	bool IsComplete() const { return m_isComplete; }
	bool IsDropping() const { return m_isDropping; }
	IngredientType GetType() const { return m_type; }
	float GetWidth() const { return m_width; }

	size_t GetSegmentCount() const { return m_walkedSegments.size(); }
	bool IsSegmentWalked(size_t index) const;

private:
	void UpdateWalkProgress();
	void UpdateDrop();
	void ResetWalkProgress();
	void AwardDropScore() const;

	bool AreAllSegmentsWalked() const;

	IngredientType m_type{};
	float m_width{};
	std::vector<float> m_dropStops{};
	size_t m_nextDropIndex{};

	std::vector<bool> m_walkedSegments{ false, false, false, false };

	bool m_isDropping{};
	bool m_isComplete{};
	int m_lastTriggerPlayerIndex{ -1 };

	// This ingredient knows about another ingredient below it,but it does not own it
	BurgerIngredientComponent* m_pIngredientBelow{};

	const float PLAYER_WIDTH{ 32.f };
	const float DROP_SPEED{ 180.f };
	const float VERTICAL_OVERLAP_TOLERANCE{ 18.f };
	const float CHAIN_TRIGGER_TOLERANCE{ 10.f };
	const int SEGMENT_COUNT{ 4 };
};