#pragma once
#include "Command.h"

class ToggleDebugCommand final : public dae::Command
{
public:
	ToggleDebugCommand() = default;
	void Execute() override;
};