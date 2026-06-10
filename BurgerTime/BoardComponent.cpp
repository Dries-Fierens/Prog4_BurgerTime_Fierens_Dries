#include "BoardComponent.h"
#include "Renderer.h"
#include <SDL3/SDL.h>
#include <cmath>
#include <limits>

// non-owning reference to the currently active BoardComponent
const BoardComponent* BoardComponent::m_pActiveBoard{ nullptr };

BoardComponent::BoardComponent(std::vector<PlatformData> platforms, std::vector<LadderData> ladders, dae::GameObject* pOwner)
	: BaseComponent(pOwner)
	, m_platforms(std::move(platforms))
	, m_ladders(std::move(ladders))
{
	m_pActiveBoard = this;
}

BoardComponent::~BoardComponent()
{
	if (m_pActiveBoard == this)
	{
		m_pActiveBoard = nullptr;
	}
}

void BoardComponent::Update()
{
}

void BoardComponent::Render() const
{
	auto* pRenderer = dae::Renderer::GetInstance().GetSDLRenderer();
	if (pRenderer == nullptr)
	{
		return;
	}

	SDL_SetRenderDrawBlendMode(pRenderer, SDL_BLENDMODE_BLEND);

	SDL_SetRenderDrawColor(pRenderer, 255, 0, 0, 180);
	for (const auto& platform : m_platforms)
	{
		SDL_RenderLine(pRenderer,
			platform.position.x,
			platform.position.y,
			platform.position.x + platform.width,
			platform.position.y);
	}

	SDL_SetRenderDrawColor(pRenderer, 255, 170, 0, 180);
	for (const auto& ladder : m_ladders)
	{
		SDL_FRect ladderRect{};
		ladderRect.x = ladder.position.x - LADDER_SNAP_TOLERANCE;
		ladderRect.y = ladder.position.y - LADDER_VERTICAL_TOLERANCE;
		ladderRect.w = LADDER_SNAP_TOLERANCE * 2.f;
		ladderRect.h = ladder.height + LADDER_VERTICAL_TOLERANCE * 2.f;
		SDL_RenderRect(pRenderer, &ladderRect);
	}
}

glm::vec3 BoardComponent::GetValidatedPosition(const glm::vec3& currentPosition,
	const glm::vec3& proposedPosition, float actorWidth, float actorHeight, bool moveHorizontally) const
{
	if (moveHorizontally)
	{
		float platformY{};
		if (!TryGetStandingPlatformY(currentPosition, actorWidth, actorHeight, platformY) &&
			!TryGetStandingPlatformY(proposedPosition, actorWidth, actorHeight, platformY))
		{
			return currentPosition;
		}

		return glm::vec3{ proposedPosition.x, platformY - actorHeight, currentPosition.z };
	}

	float snappedX{};
	if (!TryGetLadderSnapX(currentPosition, actorWidth, actorHeight, snappedX) &&
		!TryGetLadderSnapX(proposedPosition, actorWidth, actorHeight, snappedX))
	{
		float platformY{};
		if (TryGetStandingPlatformY(currentPosition, actorWidth, actorHeight, platformY))
		{
			return glm::vec3{ currentPosition.x, platformY - actorHeight, currentPosition.z };
		}

		return currentPosition;
	}

	for (const auto& ladder : m_ladders)
	{
		if (std::abs(ladder.position.x - (snappedX + actorWidth * 0.5f)) > LADDER_SNAP_TOLERANCE)
		{
			continue;
		}

		if (!IsWithinLadderBounds(ladder, proposedPosition.y, actorHeight))
		{
			continue;
		}

		glm::vec3 validatedPosition{ snappedX, proposedPosition.y, currentPosition.z };

		float platformY{};
		if (TryGetStandingPlatformY(validatedPosition, actorWidth, actorHeight, platformY))
		{
			validatedPosition.y = platformY - actorHeight;
		}

		return validatedPosition;
	}

	return currentPosition;
}

bool BoardComponent::TryGetBestLadderX(const glm::vec3& currentPosition, const glm::vec3& targetPosition,
	float actorWidth, float actorHeight, float& ladderX) const
{
	const float currentFeetY = GetFeetY(currentPosition, actorHeight);
	const float targetFeetY = GetFeetY(targetPosition, actorHeight);

	if (std::abs(currentFeetY - targetFeetY) <= PLATFORM_TOLERANCE)
	{
		return false;
	}

	const bool moveUp = targetFeetY < currentFeetY;
	const float actorCenterX = currentPosition.x + actorWidth * 0.5f;

	float bestDistance{ std::numeric_limits<float>::max() };
	bool foundLadder{};

	for (const auto& ladder : m_ladders)
	{
		const float ladderTop = ladder.position.y;
		const float ladderBottom = ladder.position.y + ladder.height;

		const bool touchesCurrentLevel =
			currentFeetY >= ladderTop - LADDER_VERTICAL_TOLERANCE &&
			currentFeetY <= ladderBottom + LADDER_VERTICAL_TOLERANCE;

		if (!touchesCurrentLevel)
		{
			continue;
		}

		const bool usefulLadder = moveUp
			? ladderTop < currentFeetY - PLATFORM_TOLERANCE
			: ladderBottom > currentFeetY + PLATFORM_TOLERANCE;

		if (!usefulLadder)
		{
			continue;
		}

		const float distance = std::abs(actorCenterX - ladder.position.x);
		if (distance < bestDistance)
		{
			bestDistance = distance;
			ladderX = ladder.position.x;
			foundLadder = true;
		}
	}

	return foundLadder;
}

const BoardComponent* BoardComponent::GetActiveBoard()
{
	return m_pActiveBoard;
}

bool BoardComponent::TryGetStandingPlatformY(const glm::vec3& position, float actorWidth, float actorHeight, float& platformY) const
{
	const float feetY = GetFeetY(position, actorHeight);
	const float centerX = position.x + actorWidth * 0.5f;

	for (const auto& platform : m_platforms)
	{
		if (std::abs(feetY - platform.position.y) > PLATFORM_TOLERANCE)
		{
			continue;
		}

		const float left = platform.position.x;
		const float right = platform.position.x + platform.width;

		if (centerX >= left && centerX <= right)
		{
			platformY = platform.position.y;
			return true;
		}
	}

	return false;
}

bool BoardComponent::TryGetLadderSnapX(const glm::vec3& position, float actorWidth, float actorHeight, float& snappedX) const
{
	const float actorCenterX = position.x + actorWidth * 0.5f;
	const float feetY = GetFeetY(position, actorHeight);

	for (const auto& ladder : m_ladders)
	{
		if (std::abs(actorCenterX - ladder.position.x) > LADDER_SNAP_TOLERANCE)
		{
			continue;
		}

		const float top = ladder.position.y - LADDER_VERTICAL_TOLERANCE;
		const float bottom = ladder.position.y + ladder.height + LADDER_VERTICAL_TOLERANCE;

		const bool overlapsVertically = feetY >= top && position.y <= bottom;
		const bool nearEnds =
			std::abs(feetY - ladder.position.y) <= LADDER_VERTICAL_TOLERANCE ||
			std::abs(feetY - (ladder.position.y + ladder.height)) <= LADDER_VERTICAL_TOLERANCE;

		if (overlapsVertically || nearEnds)
		{
			snappedX = ladder.position.x - actorWidth * 0.5f;
			return true;
		}
	}

	return false;
}

bool BoardComponent::IsWithinLadderBounds(const LadderData& ladder, float yPosition, float actorHeight) const
{
	const float feetY = GetFeetY(glm::vec3{ 0.f, yPosition, 0.f }, actorHeight);
	const float top = ladder.position.y - LADDER_VERTICAL_TOLERANCE;
	const float bottom = ladder.position.y + ladder.height + LADDER_VERTICAL_TOLERANCE;

	return feetY >= top && yPosition <= bottom;
}

float BoardComponent::GetFeetY(const glm::vec3& position, float actorHeight) const
{
	return position.y + actorHeight;
}