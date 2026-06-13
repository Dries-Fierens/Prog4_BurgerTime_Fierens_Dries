#pragma once
#include "Command.h"

class MainMenuCommand : public dae::Command
{
public:
	MainMenuCommand() = default;
	void Execute() override;
};
