#pragma once
#include "Command.h"

class StartVersusCommand : public dae::Command
{
public:
	StartVersusCommand() = default;
	void Execute() override;
};

