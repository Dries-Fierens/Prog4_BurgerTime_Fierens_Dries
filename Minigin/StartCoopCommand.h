#pragma once
#include "Command.h"

class StartCoopCommand : public dae::Command
{
public:
	StartCoopCommand() = default;
	void Execute() override;
};

