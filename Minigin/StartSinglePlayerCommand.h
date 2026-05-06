#pragma once
#include "Command.h"

class StartSingleplayerCommand : public dae::Command
{
public:
	StartSingleplayerCommand() = default;
	void Execute() override;
};