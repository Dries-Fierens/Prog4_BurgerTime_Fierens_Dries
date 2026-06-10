#pragma once
#include "BaseComponent.h"
#include "LevelData.h"
#include <glm/vec3.hpp>
#include <vector>

class BoardComponent final : public dae::BaseComponent
{
public:
	BoardComponent(std::vector<PlatformData> platforms, std::vector<LadderData> ladders, dae::GameObject* pOwner);
	~BoardComponent() override;

	void Update() override;
	void Render() const override;

	glm::vec3 GetValidatedPosition(const glm::vec3& currentPosition, const glm::vec3& proposedPosition,
		float actorWidth, float actorHeight, bool moveHorizontally) const;

	bool TryGetBestLadderX(const glm::vec3& currentPosition, const glm::vec3& targetPosition,
		float actorWidth, float actorHeight, float& ladderX) const;

	static const BoardComponent* GetActiveBoard();

private:
	bool TryGetStandingPlatformY(const glm::vec3& position, float actorWidth, float actorHeight, float& platformY) const;
	bool TryGetLadderSnapX(const glm::vec3& position, float actorWidth, float actorHeight, float& snappedX) const;
	bool IsWithinLadderBounds(const LadderData& ladder, float yPosition, float actorHeight) const;
	float GetFeetY(const glm::vec3& position, float actorHeight) const;

	std::vector<PlatformData> m_platforms{};
	std::vector<LadderData> m_ladders{};

	static const BoardComponent* m_pActiveBoard;

	const float PLATFORM_TOLERANCE{ 10.f };
	const float LADDER_SNAP_TOLERANCE{ 15.f };
	const float LADDER_VERTICAL_TOLERANCE{ 6.f };
};